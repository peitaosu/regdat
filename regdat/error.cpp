// MIT License
//
// Copyright (c) 2019-2020 Tony Su
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

#include "error.h"

namespace regdat {
    std::string get_error_message(int error)
    {
        if(Errors.find(error) != Errors.end()){
            return Errors.find(error)->second;
        }else{
            return "Error message undefined.";
        }
    }

    void print_error(int error)
    {
        std::cout << "[ERROR] " << get_error_message(error) << std::endl;
    }

    void print_error(int level, int error)
    {
        std::string level_string = "[ERROR]";
        if (level == DEBUG_INFO) {
            level_string = "[WARNN]";
        }
        if (level == USER_INFO) {
            level_string = "[INFOR]";
        }
        std::cout << level_string << " " << get_error_message(error) << std::endl;
    }

    void print_error(int level, int error, std::string detail)
    {
        std::string level_string = "[ERROR]";
        if (level == DEBUG_INFO) {
            level_string = "[WARNN]";
        }
        if (level == USER_INFO) {
            level_string = "[INFOR]";
        }
        std::cout << level_string << " " << get_error_message(error) << " : " << detail << std::endl;
    }
}
