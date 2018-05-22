#include <cstdlib>
#include <cmath>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

void check_base(int base)
{
    if(base < 2 || base > 16)
        throw std::runtime_error("Podstawa spoza zakresu 2 - 16.\n");
}

void check_input_number(int decimal)
{
    if(abs(decimal) > 1000000000)
        throw std::runtime_error("Liczba poza przewidywanym zakresem wejścia.\n");
}

void check_digits(std::string &number, int base, bool has_sign)
{
    int digits_begin = has_sign ? 1 : 0;
    char max_dec = (char)std::min(57, base+47);
    char max_big_hex = (char)std::max(64, base+54);
    char max_small_hex = (char)std::max(96, base+86);

    for(auto it = number.begin() + digits_begin ; it != number.end(); ++it)
    {
        if(*it < '0' || (*it > max_dec && *it < 'A') || (*it > max_big_hex && *it < 'a')
           || *it > max_small_hex)
            throw std::runtime_error("Znaki niewłaściwe dla podanego systemu liczbowego.\n");
    }
}

int to_decimal(std::string & number, int base)
{
    auto actual_digit = [](const char & d)
        {
            if(d >= '0' && d <= '9')
                return +d - '0';

            if(d >= 'A' && d <= 'F')
                return +d - 'A' + 10;

            if(d >= 'a' && d <= 'f')
                return +d - 'a' + 10;

            return 0;
        };

    return std::accumulate(number.begin(), number.end(), 0,
        [=](int decimal, const char & d){ return decimal * base + actual_digit(d); });
}

std::vector<int> to_output(int decimal, int base)
{
    std::vector<int> output;

    do
    {
        output.push_back(decimal % base);
        decimal = decimal / base;
    }
    while(decimal != 0);

    return output;
}

int main()
{
    int base_in;
    std::string number_in;

    std::cout << "\t\tCONVERTER SYSTEMÓW LICZBOWYCH\n\n";
    std::cout << "Podaj podstawę systemu liczby\n";
    std::cin >> base_in;
    std::cout << "\n";
    check_base(base_in);
    std::cout << "Podaj liczbę do zamiany\n";
    std::cin >> number_in;

    bool has_sign = number_in[0] == '-' || number_in[0] == '+';

    check_digits(number_in, base_in, has_sign);

    int base_out, decimal = to_decimal(number_in, base_in);

    check_input_number(decimal);
    std::cout << "\n" << "Podaj podstawę systemu, na który chcesz zamienić tę liczbę\n";
    std::cin >> base_out;
    std::cout << "\n\n";
    check_base(base_out);

    std::vector<int> number_out = to_output(decimal, base_out);

    std::cout << "\tTwoja liczba w systemie o podstawie " << base_out << " wynosi:\n\n" << "\t\t";

    if(has_sign && number_in[0] == '-')
        std::cout << "-";

    for(auto it = number_out.rbegin(); it != number_out.rend(); ++it)
    {
        int shift = *it < 10 ? '0' : 'A';
        char out_code = *it % 10 + shift;

        std::cout << (char)out_code;
    }

    std::cout << "\n\n";

    return 0;
}
