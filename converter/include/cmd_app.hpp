#ifndef _CMD_APP_HPP_
#define _CMD_APP_HPP_

#include <cstdlib>
#include <iostream>
#include <string>

class cmd_app
{
public:
    cmd_app()
    {
    }

    ~cmd_app() = default;
    cmd_app(const cmd_app &) = delete;
    cmd_app(cmd_app &&) = delete;
    cmd_app & operator=(const cmd_app &) = delete;
    cmd_app & operator=(cmd_app &&) = delete;

private:
    void run();
};

#endif
