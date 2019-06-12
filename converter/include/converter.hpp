#ifndef CONVERTER_HPP_
#define CONVERTER_HPP_

#include <cstdlib>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

class converter_exception : public std::logic_error
{
public:
    explicit converter_exception(const std::string & s) : std::logic_error(s)
    {
    }
};

class converter
{
private:
    enum sign
    {
        minus,
        plus,
        unspec
    };

public:
    converter(int base_in, int base_out);
    ~converter() = default;
    converter(converter &&) = delete;
    converter(const converter &) = delete;
    converter & operator=(converter &&) = delete;
    converter & operator=(const converter &) = delete;

    std::string convert(const std::string & number) const;

private:
    sign get_sign(const std::string & number) const;
    void validate_digits(sign sgn, const std::string & number) const;
    long long int to_decimal(const std::string & number) const;
    std::vector<int> to_base_out(long long int decimal) const;
    std::string build_number(sign sgn, const std::vector<int> & number) const;

    int base_in, base_out;
};

#endif
