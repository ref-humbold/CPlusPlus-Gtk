#include "IPAddress.hpp"

IPAddress::IPAddress() :
    address{0}
{
}

IPAddress::IPAddress(addr_t address) :
    address{address}
{
}

IPAddress::IPAddress(const std::string & address) :
    address{parse(address)}
{
}

IPAddress::operator addr_t() const
{
    return address;
}

IPAddress::operator std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>() const
{
    return std::make_tuple((address & 0xFF000000) >> 24, (address & 0xFF0000) >> 16,
                            (address & 0xFF00) >> 8, address & 0xFF);
}

IPAddress::operator std::string() const
{
    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> bytes = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(*this);

    return std::to_string(std::get<0>(bytes)) + "." + std::to_string(std::get<1>(bytes)) + "."
           + std::to_string(std::get<2>(bytes)) + "." + std::to_string(std::get<3>(bytes));
}

addr_t IPAddress::parse(const std::string & addr)
{
    std::vector<std::string> splitted;
    std::vector<addr_t> addr_bytes;
    size_t begin_pos = 0;

    while(begin_pos != std::string::npos)
    {
        size_t end_pos = addr.find(".", begin_pos);

        if(end_pos != std::string::npos)
        {
            splitted.push_back(addr.substr(begin_pos, end_pos - begin_pos));
            begin_pos = end_pos + 1;
        }
        else
        {
            splitted.push_back(addr.substr(begin_pos));
            begin_pos = end_pos;
        }
    }

    if(splitted.size() != 4)
        throw IPAddressException("Parameter is not a valid IP adress.");

    for(const auto & s : splitted)
        if(s == "" || std::any_of(s.begin(), s.end(), [](char c){ return c < '0' || c > '9'; }))
            throw IPAddressException("Parameter is not a valid IP adress.");

    addr_bytes.resize(splitted.size());
    std::transform(splitted.begin(), splitted.end(), addr_bytes.begin(),
                   [](const std::string & s){ return stoul(s); });

    if(std::any_of(addr_bytes.begin(), addr_bytes.end(), [](addr_t p){ return p > 255; }))
        throw IPAddressException("Parameter is not a valid IP adress.");

    return std::accumulate(addr_bytes.begin(), addr_bytes.end(), 0,
                           [](addr_t acc, addr_t b){ return (acc << 8) | b; });
}
