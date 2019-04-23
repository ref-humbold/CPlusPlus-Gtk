#include "converter.hpp"

using namespace std::string_literals;

converter::converter(int base_in, int base_out) : base_in{base_in}, base_out{base_out}
{
    if(base_in < 2 || base_in > 16)
        throw converter_exception("Invalid input base ("s + std::to_string(base_in)
                                  + "), must be between 2 and 16"s);

    if(base_out < 2 || base_out > 16)
        throw converter_exception("Invalid output base ("s + std::to_string(base_out)
                                  + "), must be between 2 and 16"s);
}

std::string converter::convert(const std::string & number) const
{
    sign sgn = get_sign(number);

    validate_digits(sgn, number);

    if(base_in == base_out)
        return number;

    long long int decimal = to_decimal(number);
    std::vector<int> number_out = to_base_out(decimal);

    return build_number(sgn, number_out);
}

converter::sign converter::get_sign(const std::string & number) const
{
    switch(number.at(0))
    {
        case '-':
            return minus;

        case '+':
            return plus;

        default:
            return unspec;
    }
}

void converter::validate_digits(converter::sign sgn, const std::string & number) const
{
    size_t digits_begin = sgn != unspec ? 1 : 0;
    char max_dec = static_cast<char>(std::min(57LL, base_in + 47LL));
    char max_big_hex = static_cast<char>(std::max(64LL, base_in + 54LL));
    char max_small_hex = static_cast<char>(std::max(96LL, base_in + 86LL));

    if(number.length() == digits_begin)
        throw converter_exception("No number specified"s);

    for(auto it = number.begin() + digits_begin; it != number.end(); ++it)
    {
        if(*it < '0' || (*it > max_dec && *it < 'A') || (*it > max_big_hex && *it < 'a')
           || *it > max_small_hex)
            throw converter_exception("Character \'"s + std::string(1, *it)
                                      + "\' is invalid for numeral system of base "s
                                      + std::to_string(base_in));
    }
}

long long int converter::to_decimal(const std::string & number) const
{
    auto actual_digit = [](char d) {
        if(d >= '0' && d <= '9')
            return +d - '0';

        if(d >= 'A' && d <= 'F')
            return +d - 'A' + 10;

        if(d >= 'a' && d <= 'f')
            return +d - 'a' + 10;

        return 0;
    };

    return std::accumulate(number.begin(), number.end(), 0LL, [=](long long int decimal, char d) {
        long long int res = decimal * base_in + actual_digit(d);

        if(res < 0)
            throw converter_exception("Number too large"s);

        return res;
    });
}

std::vector<int> converter::to_base_out(long long int decimal) const
{
    std::vector<int> output;

    do
    {
        output.push_back(decimal % base_out);
        decimal /= base_out;
    } while(decimal != 0);

    return output;
}

std::string converter::build_number(converter::sign sgn, const std::vector<int> & number) const
{
    std::string result;

    if(sgn == minus)
        result.push_back('-');

    for(auto it = number.rbegin(); it != number.rend(); ++it)
    {
        int shift = *it < 10 ? '0' : 'A';

        result.push_back(*it % 10 + shift);
    }

    return result;
}
