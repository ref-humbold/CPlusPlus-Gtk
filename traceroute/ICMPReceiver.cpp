#include "ICMPReceiver.hpp"

std::vector<uint8_t> ICMPReceiver::receive()
{
    socklen_t sender_size = sizeof(sender_address);
    uint8_t msg_buf[IP_MAXPACKET];

    ssize_t msg_size = recvfrom(socket.get_descriptor(), msg_buf, IP_MAXPACKET, MSG_DONTWAIT,
                                (sockaddr *)&sender_address, &sender_size);

    if(msg_size < 0)
        throw SocketException(strerror(errno));

    return std::vector<uint8_t>(std::begin(msg_buf), std::begin(msg_buf) + msg_size);
}

IPAddress ICMPReceiver::take_address()
{
    char ip_str[32];

    const char * result = inet_ntop(AF_INET, &(sender_address.sin_addr), ip_str, sizeof(ip_str));

    if(result == nullptr)
        throw SocketException(strerror(errno));

    return IPAddress(std::string(ip_str));
}
