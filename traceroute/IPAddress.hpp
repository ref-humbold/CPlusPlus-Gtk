// Rafał Kaleta, 272655
#ifndef IP_ADDRESS_HPP
#define IP_ADDRESS_HPP

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <array>
#include <string>
#include <tuple>
#include <algorithm>

using addr_t = unsigned int;

class IPAddressException : public std::runtime_error
{
public:
    IPAddressException(const std::string & s) :
        std::runtime_error(s)
    {
    }
};

class IPAddress
{
private:
    addr_t address;

public:
    IPAddress();
    IPAddress(addr_t address);
    IPAddress(const std::string & address);

    bool operator ==(IPAddress addr) const
    {
        return this->address == addr.address;
    }

    bool operator !=(IPAddress addr) const
    {
        return !(*this == addr);
    }

    bool operator <(IPAddress addr) const
    {
        return this->address < addr.address;
    }

    bool operator >(IPAddress addr) const
    {
        return !(*this < addr) && (*this != addr);
    }

    bool operator <=(IPAddress addr) const
    {
        return (*this < addr) || (*this == addr);
    }

    bool operator >=(IPAddress addr) const
    {
        return !(*this < addr);
    }

    explicit operator addr_t() const;
    explicit operator std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>() const;
    explicit operator std::string() const;

private:
    addr_t parse(const std::string & addr);
};

#endif
