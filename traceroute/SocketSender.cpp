#include "SocketSender.hpp"

void SocketSender::send(const void * msg_buf, int msg_size, int ttl)
{
    setsockopt(socket->get_desc(), IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

    ssize_t sent_size = sendto(socket->get_desc(), msg_buf, msg_size, 0,
        (sockaddr*)&receiver_sck, sizeof(receiver_sck));

    if(sent_size < 0)
        throw SocketException(strerror(errno));
}

void SocketSender::set_receiver(const std::string & ip_addr)
{
    receiver_sck.sin_family = AF_INET;

    int result = inet_pton(AF_INET, ip_addr.c_str(), &receiver_sck.sin_addr);

    if(result < 1)
        throw SocketException("Invalid addressing.");
}

std::unique_ptr<icmphdr> SocketSender::prepare_icmp(uint16_t id, uint16_t seq)
{
    std::unique_ptr<icmphdr> header = std::unique_ptr<icmphdr>(new icmphdr);

    header->type = ICMP_ECHO;
    header->code = 0;
    header->un.echo.id = id;
    header->un.echo.sequence = seq;
    header->checksum = 0;
    header->checksum = count_checksum((uint16_t *)(header.get()), sizeof(*header));

    return header;
}

uint16_t SocketSender::count_checksum(const uint16_t * hdr, int length)
{
    if((length&1) == 1)
        throw SocketException("Incorrect length of ICMP header.");

    uint32_t sum = 0;
    const uint16_t * ptr = hdr;

    for(int i = 0; i < length; i += 2)
    {
        sum += *ptr;
        ++ptr;
    }

    sum = (sum>>16)+(sum&0xFFFF);

    return (uint16_t)(~(sum+(sum>>16)));
}
