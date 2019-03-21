#include <cstdlib>
#include <string>
#include <vector>
#include <unistd.h>
#include "cmd_app.hpp"

std::vector<std::string> parse_args(int argc, char * argv[])
{
}

int main(int argc, char * argv[])
{
    std::vector<std::string> arguments = parse_args(argc, argv);

    cmd_app(arguments).run();

    return 0;
}
