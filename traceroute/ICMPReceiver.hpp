#ifndef ICMP_RECEIVER_HPP
#define ICMP_RECEIVER_HPP

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

#include "RawSocket.hpp"

class ICMPReceiver
{
private:
    std::shared_ptr<RawSocket> socket;
    sockaddr_in sender_sck;

public:
    ICMPReceiver(std::shared_ptr<RawSocket> s) :
        socket{s}
    {
    }

    std::vector<uint8_t> receive();
    std::string take_address();
};

#endif
