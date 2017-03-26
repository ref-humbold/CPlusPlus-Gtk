#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <exception>

class SocketException : public std::runtime_error
{
    public:
    SocketException(const std::string & s) :
        std::runtime_error(s)
    {
    }
};

class RawSocket
{
    int desc;

    public:
    RawSocket() :
        desc{socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)}
    {
        if(desc < 0)
            throw SocketException(strerror(errno));
    }

    ~RawSocket()
    {
        close(desc);
    }

    RawSocket(const RawSocket & raw_sck) = default;
    RawSocket(RawSocket && raw_sck) = default;
    RawSocket & operator=(const RawSocket & raw_sck) = default;
    RawSocket & operator=(RawSocket && raw_sck) = default;

    int get_desc()
    {
        return desc;
    }
};

#endif
