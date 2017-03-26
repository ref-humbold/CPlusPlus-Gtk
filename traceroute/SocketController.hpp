#ifndef SOCKET_CONTROLLER_HPP
#define SOCKET_CONTROLLER_HPP

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <string>
#include <memory>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "RawSocket.hpp"
#include "SocketReceiver.hpp"
#include "SocketSender.hpp"

class SocketController
{
    std::shared_ptr<RawSocket> socket;
    SocketSender sender;
    SocketReceiver receiver;

    public:
    SocketController(std::shared_ptr<RawSocket> s) :
        socket{s},
        sender{SocketSender(socket)},
        receiver{SocketReceiver(socket)}
    {
    }
};

#endif
