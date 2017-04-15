#ifndef ICMP_CONTROLLER_HPP
#define ICMP_CONTROLLER_HPP

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <sys/time.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <exception>
#include <string>
#include <tuple>
#include <set>
#include <memory>

#include "RawSocket.hpp"
#include "ICMPReceiver.hpp"
#include "ICMPSender.hpp"

class NotMyReplyException : public std::runtime_error
{
public:
    NotMyReplyException(const std::string & s) :
        std::runtime_error(s)
    {
    }
};

class TimeExceededException : public std::runtime_error
{
public:
    TimeExceededException(const std::string & s) :
        std::runtime_error(s)
    {
    }
};

class ICMPController
{
    std::shared_ptr<RawSocket> socket;
    ICMPSender sender;
    ICMPReceiver receiver;

public:
    ICMPController(std::shared_ptr<RawSocket> s) :
        socket{s},
        sender{ICMPSender(socket)},
        receiver{ICMPReceiver(socket)}
    {
    }

    void echo_request(const std::string & addr, uint16_t id, uint16_t seq, int ttl);
    std::tuple<std::set<std::string>, int> echo_reply(uint16_t id, uint16_t seq);

private:
    std::string recv_echo(uint16_t id, uint16_t seq);
    std::tuple<iphdr *, icmphdr *, uint8_t *> take_headers(uint8_t * ptr);
};

#endif
