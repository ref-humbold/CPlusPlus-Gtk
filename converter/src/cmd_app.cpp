#include <cmd_app.hpp>

cmd_app::cmd_app(const std::vector<std::string> & args)
{
    base_in = parse_base(args.at(0));
    base_out = parse_base(args.at(1));
    numbers = args;
}

void cmd_app::run()
{
    converter conv(base_in, base_out);

    for(auto it = numbers.begin() + 2; it != numbers.end(); ++it)
        convert(*it, conv);

    if(numbers.size() == 2)
        while(true)
        {
            std::string n;

            std::cin >> n;
            convert(n, conv);
        }
}

int cmd_app::parse_base(const std::string & s)
{
    size_t n;
    int v;

    if(s == "")
        return defbase;

    try
    {
        v = stoi(s, &n);
    }
    catch(const std::invalid_argument & e)
    {
        throw base_exception("Given base is not a number");
    }

    if(n < s.length())
        throw base_exception("Given base is not a number");

    return v;
}

void cmd_app::convert(const std::string & from, const converter & conv)
{
    std::cout << from << " @" << base_in << " => ";

    try
    {
        std::cout << conv.convert(from) << " @" << base_out << "\n";
    }
    catch(const converter_exception & e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
    }
}
