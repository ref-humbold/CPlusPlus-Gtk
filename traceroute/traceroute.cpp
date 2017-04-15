#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <string>
#include <set>
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
            beginPos = endPos + 1;
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

void print_results(int ttl, const std::set<std::string> & recvaddr, int avg_time)
{
    std::cout << ttl << ". ";

    if(avg_time < 0)
    {
        if(recvaddr.size() == 0)
            std::cout << "*\n";
        else
        {
            for(auto ars : recvaddr)
                std::cout << ars << " ";

            std::cout << "???\n";
        }
    }
    else
    {
        for(auto ars : recvaddr)
            std::cout << ars << " ";

        std::cout << avg_time / 1000 << "ms\n";
    }
}

bool send_msg(SocketController & sck, const std::string & addr, int ttl)
{
    uint16_t pid = getpid();
    int seq = ttl;

    sck.echo_request(addr, pid, seq, ttl);

    std::set<std::string> recvaddr;
    int avg_time;

    try
    {
        std::tie(recvaddr, avg_time) = sck.echo_reply(pid, seq);
    }
    catch(const TimeExceededException & e)
    {
        avg_time = -1;
    }

    print_results(ttl, recvaddr, avg_time);

    return std::any_of(recvaddr.begin(), recvaddr.end(),
        [addr](const std::string & s){ return s == addr; });
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

    for(int i = 1; i <= 30; ++i)
        if(send_msg(socket_ctrl, address, i))
            break;

    return 0;
}
