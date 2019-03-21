#include <cmd_app.hpp>

void cmd_app::run()
{
    converter conv(base_in, base_out);

    for(const auto & n : numbers)
        std::cout << conv.convert(n);
}
