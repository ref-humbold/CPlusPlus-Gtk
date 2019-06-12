#ifndef CMD_APP_HPP_
#define CMD_APP_HPP_

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "converter.hpp"

class base_exception : public std::logic_error
{
public:
    explicit base_exception(const std::string & s) : std::logic_error(s)
    {
    }
};

class cmd_app
{
public:
    explicit cmd_app(const std::vector<std::string> & args);
    ~cmd_app() = default;
    cmd_app(const cmd_app &) = delete;
    cmd_app(cmd_app &&) = delete;
    cmd_app & operator=(const cmd_app &) = delete;
    cmd_app & operator=(cmd_app &&) = delete;

    void run();

private:
    int parse_base(const std::string & s);
    void convert(const std::string & from, const converter & conv);

    static constexpr int defbase = 10;
    std::vector<std::string> numbers;
    int base_in, base_out;
};

#endif
