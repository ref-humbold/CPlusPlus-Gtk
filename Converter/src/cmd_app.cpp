#include "cmd_app.hpp"

void cmd_app::run()
{
    converter conv(params.base_in, params.base_out);

    if(params.numbers.size() > 0)
        for(auto n : params.numbers)
            convert(n, conv);
    else
        while(true)
        {
            std::string n;

            std::cin >> n;

            if(n == ".")
                break;

            convert(n, conv);
        }
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
