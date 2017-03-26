#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>

#include "RawSocket.hpp"
#include "SocketController.hpp"

bool check_address(const std::string & addr)
{
    std::vector<std::string> splitted;
    size_t beginPos = 0;

    while(beginPos != std::string::npos)
    {
        size_t endPos = addr.find(".", beginPos);

        if(endPos != std::string::npos)
        {
            splitted.push_back(addr.substr(beginPos, endPos-beginPos));
            beginPos = endPos+1;
        }
        else
        {
            splitted.push_back(addr.substr(beginPos));
            beginPos = endPos;
        }
    }

    if(splitted.size() != 4)
        return false;

    for(const auto & s : splitted)
        if(s == "" || std::any_of(s.begin(), s.end(), [](char c){ return c < '0' || c > '9'; }))
            return false;

    if(std::any_of(splitted.begin(), splitted.end(),
       [](const std::string & s){ return stoi(s) < 0 || stoi(s) > 255; }))
        return false;

    return true;
}

int main(int argc, char * argv[])
{
    std::shared_ptr<RawSocket> socket = std::make_shared<RawSocket>();
    SocketController socket_ctrl = SocketController(socket);

    if(argc < 2)
        throw std::invalid_argument("No destination IP specified");

    std::string address = argv[1];

    if(!check_address(address))
        throw std::invalid_argument("Not an IP address.");

    return 0;
}
