#pragma once
#include <iostream>
#include <string>

class Options
{
public:
    Options(int argc, char **argv);
    ~Options();
    std::string get_value(const char *argv);
    std::string get_argv(int index);
    int check(const char *argv);

private:
    char **argv;
    int   argc;
};

