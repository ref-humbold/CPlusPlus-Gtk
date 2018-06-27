#ifndef _ICMP_RECEIVER_HPP_
#define _ICMP_RECEIVER_HPP_

#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <algorithm>
#include <string>
#include <tuple>
#include <vector>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include "IPAddress.hpp"
#include "RawSocket.hpp"

class ICMPReceiver
{
private:
    const RawSocket & socket;
    sockaddr_in sender_address;

public:
    explicit ICMPReceiver(RawSocket & s) : socket{s}
    {
    }

    std::vector<uint8_t> receive();
    IPAddress take_address();
};

#endif
