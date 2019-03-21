#ifndef _CMD_APP_HPP_
#define _CMD_APP_HPP_

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "converter.hpp"

class cmd_app
{
public:
    explicit cmd_app(const std::vector<std::string> & args)
    {
    }

    ~cmd_app() = default;
    cmd_app(const cmd_app &) = delete;
    cmd_app(cmd_app &&) = delete;
    cmd_app & operator=(const cmd_app &) = delete;
    cmd_app & operator=(cmd_app &&) = delete;

    void run();

private:
    std::vector<std::string> numbers;
    int base_in;
    int base_out;
};

#endif
