#include <cstdlib>
#include "cmd_app.hpp"

int main(int argc, char * argv[])
{
    std::vector<std::string> arguments;

    for(int i = 1; i < argc; ++i)
        arguments.push_back(std::string(argv[i]));

    cmd_app(arguments).run();

    return 0;
}
