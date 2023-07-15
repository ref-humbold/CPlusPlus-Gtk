#ifndef CMD_APP_HPP_
#define CMD_APP_HPP_

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "converter.hpp"

class app_parameters
{
public:
    app_parameters() : base_in{default_base}, base_out{default_base}, numbers{}, verbose{false}
    {
    }

    size_t base_in, base_out;
    std::vector<std::string> numbers;
    bool verbose;

private:
    static constexpr size_t default_base = 10;
};

class cmd_app
{
public:
    explicit cmd_app(const app_parameters & params) : params{params}
    {
    }

    ~cmd_app() = default;
    cmd_app(const cmd_app &) = delete;
    cmd_app(cmd_app &&) = delete;
    cmd_app & operator=(const cmd_app &) = delete;
    cmd_app & operator=(cmd_app &&) = delete;

    void run();

private:
    void read_from_stdin(const converter & conv);
    void convert(const std::string & input, const converter & conv);

    static const std::string stdin_number;
    const app_parameters & params;
};

#endif
