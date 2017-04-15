#include "ICMPReceiver.hpp"

std::vector<uint8_t> ICMPReceiver::receive()
{
    socklen_t sender_size = sizeof(sender_sck);
    uint8_t msg_buf[IP_MAXPACKET];

    ssize_t msg_size = recvfrom(socket->get_desc(), msg_buf, IP_MAXPACKET, MSG_DONTWAIT,
        (sockaddr *)&sender_sck, &sender_size);

    if(msg_size < 0)
        throw SocketException(strerror(errno));

    return std::vector<uint8_t>(msg_buf, msg_buf+msg_size);
}

std::string ICMPReceiver::take_address()
{
    char ip_str[32];

    const char * result = inet_ntop(AF_INET, &(sender_sck.sin_addr), ip_str, sizeof(ip_str));

    if(result == NULL)
        throw SocketException(strerror(errno));

    return std::string(ip_str);
}
