#ifndef RAW_SOCKET_HPP
#define RAW_SOCKET_HPP

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <exception>
#include <stdexcept>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>

class SocketException : public std::runtime_error
{
public:
    SocketException(const std::string & s) : std::runtime_error(s)
    {
    }

    SocketException(const char * s) : std::runtime_error(s)
    {
    }
};

class RawSocket
{
private:
    int descriptor;

public:
    RawSocket(int protocol) : descriptor{socket(AF_INET, SOCK_RAW, protocol)}
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

    int get_descriptor()
    {
        return descriptor;
    }
};

#endif
