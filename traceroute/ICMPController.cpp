#include "ICMPController.hpp"

void ICMPController::echo_request(const IPAddress & addr, uint16_t id, uint16_t seq, int ttl)
{
    for(int i = 0; i < 3; ++i)
    {
        icmphdr header = sender.prepare_icmp(id, 3*seq+i);

        sender.set_receiver(addr);
        sender.send(&header, sizeof(header), ttl);
    }
}

std::tuple<std::set<IPAddress>, int> ICMPController::echo_reply(uint16_t id, uint16_t seq)
{
    std::set<IPAddress> recvaddr;
    fd_set fd;
    timeval timer;
    int avg_time = 0;
    int recvnum = 0;

    FD_ZERO(&fd);
    FD_SET(socket->get_descriptor(), &fd);
    timer.tv_sec = 1;
    timer.tv_usec = 0;

    do
    {
        int ready = select(socket->get_descriptor()+1, &fd, nullptr, nullptr, &timer);

        if(ready < 0)
            throw SocketException(strerror(errno));

        if(ready == 0 && recvnum == 0)
            throw TimeExceededException("");

        if(ready == 0 && recvnum > 0)
            return std::make_tuple(recvaddr, -1);

        IPAddress address;

        try
        {
            address = recv_echo(id, seq);
        }
        catch(const NotMyReplyException & e)
        {
            continue;
        }

        recvaddr.insert(address);
        avg_time = (avg_time + 1000000 - timer.tv_usec) / 2;
        ++recvnum;
    }
    while(recvnum < 3);

    return std::make_tuple(recvaddr, avg_time);
}

IPAddress ICMPController::recv_echo(uint16_t id, uint16_t seq)
{
    std::vector<uint8_t> message = receiver.receive();
    iphdr * hIP;
    icmphdr * hICMP;
    uint8_t * rest;

    std::tie(hIP, hICMP, rest) = take_headers(message.data());

    if(hICMP->type == 0)
    {
        if(hICMP->un.echo.id != id || hICMP->un.echo.sequence / 3 != seq)
            throw NotMyReplyException("");
    }
    else if(hICMP->type == 11)
    {
        iphdr * hIP_r;
        icmphdr * hICMP_r;

        std::tie(hIP_r, hICMP_r, std::ignore) = take_headers(rest);

        if(hICMP_r->un.echo.id != id || hICMP_r->un.echo.sequence / 3 != seq)
            throw NotMyReplyException("");
    }

    return receiver.take_address();
}

std::tuple<iphdr *, icmphdr *, uint8_t *> ICMPController::take_headers(uint8_t * ptr)
{
    iphdr * hIP = (iphdr *)ptr;
    icmphdr * hICMP = (icmphdr *)(ptr + 4 * hIP->ihl);
    uint8_t * rest = ptr + 4 * hIP->ihl+sizeof(icmphdr);

    return std::make_tuple(hIP, hICMP, rest);
}
