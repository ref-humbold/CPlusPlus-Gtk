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

    explicit converter_exception(const char * s) : std::logic_error(s)
    {
    }
};

class converter
{
public:
    converter(std::string number_in, int base_in, int base_out)
        : number_in{number_in}, base_in{base_in}, base_out{base_out}
    {
        this->has_sign = number_in[0] == '-' || number_in[0] == '+';
        this->validate_digits();
    }

    ~converter() = default;
    converter(converter &&) = delete;
    converter(const converter &) = delete;
    converter & operator=(converter &&) = delete;
    converter & operator=(const converter &) = delete;

    std::string convert();

private:
    void validate_digits();
    int to_decimal();
    void validate_size(int decimal);
    std::vector<int> to_base_out(int decimal);
    std::string build_number(const std::vector<int> & number);

    std::string number_in;
    int base_in, base_out;
    bool has_sign;
};

#endif
