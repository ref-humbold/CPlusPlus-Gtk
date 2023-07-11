#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h>
#include "cmd_app.hpp"

using namespace std::string_literals;

struct args_exception : public std::logic_error
{
    explicit args_exception(const std::string & s) : std::logic_error(s)
    {
    }
};

size_t parse_number(const std::string & s, const std::string & arg_name)
{
    size_t pos, value;

    try
    {
        value = std::stoul(s, &pos);
    }
    catch(const std::invalid_argument & e)
    {
        throw args_exception("Given "s + arg_name + " is not a number"s);
    }

    if(pos < s.length())
        throw args_exception("Given "s + arg_name + " is not a number"s);

    return value;
}

app_parameters parse_args(int argc, char * argv[])
{
    app_parameters params;
    const std::string optstring = ":b:B:v"s;
    int option = getopt(argc, argv, optstring.c_str());

    opterr = 0;

    while(option != -1)
    {
        switch(option)
        {
            case 'b':
                params.base_in = parse_number(optarg, "input base"s);
                break;

            case 'B':
                params.base_out = parse_number(optarg, "output base"s);
                break;

            case 'v':
                params.verbose = true;
                break;

            case '?':
                throw args_exception("Unknown option -"s + static_cast<char>(optopt));

            case ':':
                {
                    char option = static_cast<char>(optopt);

                    if(option == 'b' || option == 'B')
                        throw args_exception(
                                "Option -"s + option
                                + " requires a number between 2 and 16 as an argument"s);

                    throw args_exception("Option -"s + option + " requires an argument"s);
                }

            default:
                break;
        }

        option = getopt(argc, argv, optstring.c_str());
    }

    for(int i = optind; i < argc; ++i)
        params.numbers.push_back(argv[i]);

    return params;
}

int main(int argc, char * argv[])
try
{
    app_parameters params = parse_args(argc, argv);

    cmd_app(params).run();
    return 0;
}
catch(const std::exception & e)
{
    std::cerr << "ERROR: " << e.what() << "\n";
    return 1;
}
