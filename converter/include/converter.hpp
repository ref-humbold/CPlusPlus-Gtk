#ifndef _CONVERTER_HPP_
#define _CONVERTER_HPP_

#include <cstdlib>
#include <cmath>
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
        unspec
    };

public:
    converter(int base_in, int base_out) : base_in{base_in}, base_out{base_out}
    {
    }

    ~converter() = default;
    converter(converter &&) = delete;
    converter(const converter &) = delete;
    converter & operator=(converter &&) = delete;
    converter & operator=(const converter &) = delete;

    std::string convert(const std::string & number);

private:
    sign get_sign(const std::string & number);
    void validate_digits(sign sgn, const std::string & number);
    int to_decimal(const std::string & number);
    void validate_size(int decimal);
    std::vector<int> to_base_out(int decimal);
    std::string build_number(sign sgn, const std::vector<int> & number);

    int base_in, base_out;
};

#endif
