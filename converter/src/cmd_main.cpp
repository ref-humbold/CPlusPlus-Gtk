#include <cstdlib>
#include "cmd_app.hpp"

class args_exception : public std::invalid_argument
{
public:
    explicit args_exception(const std::string & s) : std::invalid_argument(s)
    {
    }
};

int main(int argc, char * argv[])
{
    return 0;
}
