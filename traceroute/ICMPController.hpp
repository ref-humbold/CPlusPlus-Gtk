#ifndef ICMP_CONTROLLER_HPP
#define ICMP_CONTROLLER_HPP

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <exception>
#include <stdexcept>
#include <memory>
#include <set>
#include <string>
#include <tuple>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/time.h>

#include "ICMPReceiver.hpp"
#include "ICMPSender.hpp"
#include "IPAddress.hpp"
#include "RawSocket.hpp"

class NotMyReplyException : public std::runtime_error
{
public:
    NotMyReplyException(const std::string & s) : std::runtime_error(s)
    {
    }

    NotMyReplyException(const char * s) : std::runtime_error(s)
    {
    }
};

class TimeExceededException : public std::runtime_error
{
public:
    TimeExceededException(const std::string & s) : std::runtime_error(s)
    {
    }

    TimeExceededException(const char * s) : std::runtime_error(s)
    {
    }
};

class ICMPController
{
    std::shared_ptr<RawSocket> socket;
    ICMPSender sender;
    ICMPReceiver receiver;

public:
    ICMPController(std::shared_ptr<RawSocket> s)
        : socket{s}, sender{ICMPSender(socket)}, receiver{ICMPReceiver(socket)}
    {
    }

    void echo_request(const IPAddress & addr, uint16_t id, uint16_t seq, int ttl);
    std::tuple<std::set<IPAddress>, int> echo_reply(uint16_t id, uint16_t seq);

private:
    IPAddress recv_echo(uint16_t id, uint16_t seq);
    std::tuple<iphdr *, icmphdr *, uint8_t *> take_headers(uint8_t * ptr);
};

#endif
