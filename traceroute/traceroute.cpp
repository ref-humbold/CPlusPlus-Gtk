#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "RawSocket.hpp"
#include "SocketController.hpp"

int main(int argc, char * argv[])
{
    std::shared_ptr<RawSocket> socket = std::make_shared<RawSocket>();
    SocketController socket_ctrl = SocketController(socket);

    return 0;
}
