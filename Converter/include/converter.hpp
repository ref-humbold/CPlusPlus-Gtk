#ifndef CONVERTER_HPP_
#define CONVERTER_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <exception>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

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
        nosign
    };

public:
    converter(size_t base_in, size_t base_out);
    ~converter() = default;

    std::string convert(const std::string & number) const;

private:
    sign get_sign(const std::string & number) const;
    void validate_digits(sign sign_, const std::string & number) const;
    long long int to_decimal(const std::string & number) const;
    std::vector<size_t> to_base_out(long long int decimal) const;
    std::string build_number(sign sign_, const std::vector<size_t> & number) const;

    size_t base_in, base_out;
};

#endif
