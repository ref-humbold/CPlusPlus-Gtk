#include "cmd_app.hpp"

using namespace std::string_literals;

const std::string cmd_app::stdin_number = "-"s;

void cmd_app::run()
{
    converter conv(params.base_in, params.base_out);

    if(params.numbers.size() == 0)
        read_from_stdin(conv);
    for(auto n : params.numbers)
        if(n == stdin_number)
            read_from_stdin(conv);
        else
            convert(n, conv);
}

void cmd_app::read_from_stdin(const converter & conv)
{
    std::string n;

    while(std::cin >> n)
        convert(n, conv);
}

void cmd_app::convert(const std::string & input, const converter & conv)
{
    if(params.verbose)
        std::cout << input << " @" << params.base_in << " => ";

    try
    {
        std::string result = conv.convert(input);

        std::cout << result;

        if(params.verbose)
            std::cout << " @" << params.base_out;

        std::cout << "\n";
    }
    catch(const converter_exception & e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
    }
}
