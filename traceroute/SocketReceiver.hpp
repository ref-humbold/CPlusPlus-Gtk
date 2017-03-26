#ifndef SOCKET_RECEIVER_HPP
#define SOCKET_RECEIVER_HPP

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <memory>

#include "RawSocket.hpp"

class SocketReceiver
{
    private:
    std::shared_ptr<RawSocket> socket;
    sockaddr_in sender_sck;

    public:
    SocketReceiver(std::shared_ptr<RawSocket> s) :
        socket{s}
    {
    }

    std::vector<uint8_t> receive();
    std::string take_address();
};

#endif
