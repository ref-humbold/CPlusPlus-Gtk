#ifndef _ICMP_SENDER_HPP_
#define _ICMP_SENDER_HPP_

#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include "IPAddress.hpp"
#include "RawSocket.hpp"

class ICMPSender
{
private:
    const RawSocket & socket;
    sockaddr_in receiver_address;

public:
    explicit ICMPSender(RawSocket & s) : socket{s}
    {
    }

    void send(const void * msg_buf, int msg_size, int ttl);
    void set_receiver(const IPAddress & addr);
    icmphdr prepare_icmp(uint16_t id, uint16_t seq);

private:
    uint16_t count_checksum(const uint16_t * hdr, int length);
};

#endif
