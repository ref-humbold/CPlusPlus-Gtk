#include "SocketReceiver.hpp"

void SocketReceiver::receive()
{
    socklen_t sender_size = sizeof(sender_sck);
    uint8_t msg_buf[IP_MAXPACKET];

    ssize_t msg_size = recvfrom(socket->get_desc(), msg_buf, IP_MAXPACKET, 0,
        (sockaddr*)&sender_sck, &sender_size);

    if(msg_size < 0)
        throw SocketException(strerror(errno));

    message = std::vector<uint8_t>(msg_buf, msg_buf+msg_size);
}

std::string SocketReceiver::take_address()
{
    char ip_str[32];

    const char * result = inet_ntop(AF_INET, &(sender_sck.sin_addr), ip_str, sizeof(ip_str));

    if(result == NULL)
        throw SocketException(strerror(errno));

    return std::string(ip_str);
}

std::pair<iphdr, icmphdr> SocketReceiver::take_headers()
{
    iphdr * hIP = (iphdr *)message.data();
    icmphdr * hICMP = (icmphdr *)message.data()+4*hIP->ihl;

    return std::make_pair(*hIP, *hICMP);
}
