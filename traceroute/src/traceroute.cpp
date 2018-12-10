#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unistd.h>
#include "ICMPController.hpp"
#include "IPAddress.hpp"
#include "RawSocket.hpp"

void print_results(int ttl, const std::set<IPAddress> & recvaddr, int avg_time)
{
    std::cout << ttl << ". ";

    if(avg_time < 0)
    {
        if(recvaddr.size() == 0)
            std::cout << "*\n";
        else
        {
            for(auto addr : recvaddr)
                std::cout << std::string(addr) << " ";

            std::cout << "???\n";
        }
    }
    else
    {
        for(auto addr : recvaddr)
            std::cout << std::string(addr) << " ";

        std::cout << avg_time / 1000 << "ms\n";
    }
}

bool send_message(ICMPController & sck, const IPAddress & addr, int ttl)
{
    uint16_t pid = getpid();
    int seq = ttl;

    sck.echo_request(addr, pid, seq, ttl);

    std::set<IPAddress> recvaddr;
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
                       [addr](const IPAddress & a) { return a == addr; });
}

int main(int argc, char * argv[])
{
    RawSocket socket = RawSocket(IPPROTO_ICMP);
    ICMPController socket_ctrl = ICMPController(socket);

    if(argc < 2)
        throw std::logic_error("No destination IP specified");

    IPAddress addr(argv[1]);

    for(int i = 1; i <= 30; ++i)
        if(send_message(socket_ctrl, addr, i))
            break;

    return 0;
}
