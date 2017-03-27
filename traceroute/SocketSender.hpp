#ifndef SOCKET_SENDER_HPP
#define SOCKET_SENDER_HPP

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <string>
#include <memory>

#include "RawSocket.hpp"

class SocketSender
{
private:
    std::shared_ptr<RawSocket> socket;
    sockaddr_in receiver_sck;

public:
    SocketSender(std::shared_ptr<RawSocket> s) :
        socket{s}
    {
    }

    void send(const void * msg_buf, int msg_size, int ttl);
    void set_receiver(const std::string & addr);
    icmphdr prepare_icmp(uint16_t id, uint16_t seq);

private:
    uint16_t count_checksum(const uint16_t * hdr, int length);
};

#endif
