#ifndef IP_ADDRESS_HPP
#define IP_ADDRESS_HPP

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>

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
    IPAddress() :
        address{0}
    {
    }

    IPAddress(addr_t address) :
        address{address}
    {
    }

    IPAddress(const std::string & address);

    friend bool operator ==(const IPAddress & addr1, const IPAddress & addr2);
    friend bool operator <(const IPAddress & addr1, const IPAddress & addr2);

    explicit operator addr_t() const
    {
        return address;
    }

    explicit operator std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>() const;
    explicit operator std::string() const;

private:
    addr_t parse(const std::string & addr);
};

inline bool operator ==(const IPAddress & addr1, const IPAddress & addr2)
{
    return addr1.address == addr2.address;
}

inline bool operator !=(const IPAddress & addr1, const IPAddress & addr2)
{
    return !(addr1 == addr2);
}

inline bool operator <(const IPAddress & addr1, const IPAddress & addr2)
{
    return addr1.address < addr2.address;
}

inline bool operator <=(const IPAddress & addr1, const IPAddress & addr2)
{
    return (addr1 < addr2) || (addr1 == addr2);
}

inline bool operator >(const IPAddress & addr1, const IPAddress & addr2)
{
    return !(addr1 <= addr2);
}

inline bool operator >=(const IPAddress & addr1, const IPAddress & addr2)
{
    return !(addr1 < addr2);
}

#endif
