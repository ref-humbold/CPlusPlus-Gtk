#ifndef _RAW_SOCKET_HPP_
#define _RAW_SOCKET_HPP_

#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>

class SocketException : public std::runtime_error
{
public:
    explicit SocketException(const std::string & s) : std::runtime_error(s)
    {
    }

    explicit SocketException(const char * s) : std::runtime_error(s)
    {
    }
};

class RawSocket
{
private:
    int descriptor;

public:
    explicit RawSocket(int protocol) : descriptor{socket(AF_INET, SOCK_RAW, protocol)}
    {
        if(descriptor < 0)
            throw SocketException(strerror(errno));
    }

    ~RawSocket()
    {
        close(descriptor);
    }

    RawSocket(const RawSocket & raw_sck) = delete;
    RawSocket(RawSocket && raw_sck) = default;
    RawSocket & operator=(const RawSocket & raw_sck) = delete;
    RawSocket & operator=(RawSocket && raw_sck) = default;

    int get_descriptor() const
    {
        return descriptor;
    }
};

#endif
