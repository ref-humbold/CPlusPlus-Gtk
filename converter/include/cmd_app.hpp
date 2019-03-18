#ifndef _CMD_APP_HPP_
#define _CMD_APP_HPP_

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "converter.hpp"

class args_exception : public std::invalid_argument
{
public:
    explicit args_exception(const std::string & s) : std::invalid_argument(s)
    {
    }
};

class cmd_app
{
public:
    cmd_app(const std::vector<std::string> & args)
    {
        parse_args(args);
    }

    ~cmd_app() = default;
    cmd_app(const cmd_app &) = delete;
    cmd_app(cmd_app &&) = delete;
    cmd_app & operator=(const cmd_app &) = delete;
    cmd_app & operator=(cmd_app &&) = delete;

    void run();

private:
    void parse_args(const std::vector<std::string> & args);

    std::vector<std::string> numbers;
    int base_in;
    int base_out;
};

#endif
