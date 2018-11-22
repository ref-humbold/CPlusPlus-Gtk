#ifndef _ICMP_CONTROLLER_HPP_
#define _ICMP_CONTROLLER_HPP_

#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <exception>
#include <stdexcept>
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
    explicit NotMyReplyException(const std::string & s) : std::runtime_error(s)
    {
    }

    explicit NotMyReplyException(const char * s) : std::runtime_error(s)
    {
    }
};

class TimeExceededException : public std::runtime_error
{
public:
    explicit TimeExceededException(const std::string & s) : std::runtime_error(s)
    {
    }

    explicit TimeExceededException(const char * s) : std::runtime_error(s)
    {
    }
};

class ICMPController
{
    const RawSocket & socket;
    ICMPSender sender;
    ICMPReceiver receiver;

public:
    explicit ICMPController(RawSocket & s)
        : socket{s}, sender{ICMPSender(s)}, receiver{ICMPReceiver(s)}
    {
    }

    void echo_request(const IPAddress & addr, uint16_t id, uint16_t seq, int ttl);
    std::tuple<std::set<IPAddress>, int> echo_reply(uint16_t id, uint16_t seq);

private:
    IPAddress recv_echo(uint16_t id, uint16_t seq);
    std::tuple<iphdr *, icmphdr *, uint8_t *> take_headers(uint8_t * ptr);
};

#endif
