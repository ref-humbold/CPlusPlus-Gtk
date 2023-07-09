#include <cstdlib>
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

struct base_exception : public std::domain_error
{
    explicit base_exception(const std::string & s) : std::domain_error(s)
    {
    }
};

size_t parse_base(const std::string & s)
{
    size_t pos, base;

    try
    {
        base = std::stoi(s, &pos);
    }
    catch(const std::invalid_argument & e)
    {
        throw base_exception("Given base is not a number");
    }

    if(pos < s.length())
        throw base_exception("Given base is not a number");

    return base;
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
                params.base_in = parse_base(optarg);
                break;

            case 'B':
                params.base_out = parse_base(optarg);
                break;

            case 'v':
                params.verbose = true;
                break;

            case '?':
                throw args_exception("Unknown option -"s + static_cast<char>(optopt));

            case ':':
                throw args_exception("Option -"s + static_cast<char>(optopt)
                                     + " requires a number between 2 and 16"s);

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
