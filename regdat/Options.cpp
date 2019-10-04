#include "Options.h"

Options::Options(int argc, char ** argv)
{
    this->argc = argc;
    this->argv = argv;
}

Options::~Options()
{
}

std::string Options::get_value(const char * argv)
{
    int index = this->check(argv);
    if ((index != 0) && ((index + 1) < this->argc))
        return this->get_argv(index + 1);
    return "";
}

std::string Options::get_argv(int index)
{
    return argv[index];
}

int Options::check(const char * argv)
{
    for (int i = 0; i < argc; i++) {
        if (this->get_argv(i) == argv) {
            return i;
        }
    }
    return 0;
}
