// MIT License
//
// Copyright (c) 2019 Tony Su
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
