#include <cstdlib>
#include <string>
#include <vector>
#include <unistd.h>
#include "cmd_app.hpp"

using namespace std::string_literals;

class args_exception : public std::logic_error
{
public:
    explicit args_exception(const std::string & s) : std::logic_error(s)
    {
    }
};

std::vector<std::string> parse_args(int argc, char * argv[])
{
    const std::string optstring = ":b:B:"s;
    std::vector<std::string> args = {"", ""};
    int option = getopt(argc, argv, optstring.c_str());

    opterr = 0;

    while(option != -1)
    {
        switch(option)
        {
            case 'b':
                args[0] = optarg;
                break;

            case 'B':
                args[1] = optarg;
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
        args.push_back(argv[i]);

    return args;
}

int main(int argc, char * argv[]) try
{
    std::vector<std::string> arguments = parse_args(argc, argv);

    cmd_app(arguments).run();

    return 0;
}
catch(const std::exception & e)
{
    std::cerr << "ERROR: " << e.what() << "\n";

    return 1;
}
