#include "converter.hpp"

std::string converter::convert()
{
    if(base_in == base_out)
        return number_in;

    int decimal = to_decimal();

    validate_size(decimal);

    std::vector<int> number_out = to_base_out(decimal);

    return build_number(number_out);
}

void converter::validate_digits()
{
    size_t digits_begin = has_sign ? 1 : 0;
    char max_dec = (char)std::min(57, base_in + 47);
    char max_big_hex = (char)std::max(64, base_in + 54);
    char max_small_hex = (char)std::max(96, base_in + 86);

    if(number_in.length() == digits_begin)
        throw converter_exception("No number specified");

    for(auto it = number_in.begin() + digits_begin; it != number_in.end(); ++it)
    {
        if(*it < '0' || (*it > max_dec && *it < 'A') || (*it > max_big_hex && *it < 'a')
           || *it > max_small_hex)
            throw converter_exception("Digit \'" + std::string(1, *it)
                                      + "\' is invalid for given base");
    }
}

void converter::validate_size(int decimal)
{
    if(abs(decimal) > 2000000000)
        throw converter_exception("Number out of input scope\n");
}

int converter::to_decimal()
{
    auto actual_digit = [](const char & d) {
        if(d >= '0' && d <= '9')
            return +d - '0';

        if(d >= 'A' && d <= 'F')
            return +d - 'A' + 10;

        if(d >= 'a' && d <= 'f')
            return +d - 'a' + 10;

        return 0;
    };

    return std::accumulate(number_in.begin(), number_in.end(), 0, [=](int decimal, const char & d) {
        return decimal * base_in + actual_digit(d);
    });
}

std::vector<int> converter::to_base_out(int decimal)
{
    std::vector<int> output;

    do
    {
        output.push_back(decimal % base_out);
        decimal /= base_out;
    } while(decimal != 0);

    return output;
}

std::string converter::build_number(const std::vector<int> & number)
{
    std::string result;

    if(has_sign && number_in[0] == '-')
        result.push_back('-');

    for(auto it = number.rbegin(); it != number.rend(); ++it)
    {
        int shift = *it < 10 ? '0' : 'A';
        char out_code = *it % 10 + shift;

        result.push_back(out_code);
    }

    return result;
}
