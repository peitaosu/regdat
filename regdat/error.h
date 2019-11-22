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

#pragma once
#include "common.h"
#include "def.h"
#include <map>

namespace regdat {
    // errors
    static const std::map<int, std::string> Errors = {
        {SUCCEED, "SUCCEED"},
        {ERROR_REG_FILE_NOT_FOUND, "REG FILE NOT FOUND"},
        {ERROR_DAT_FILE_NOT_FOUND, "DAT FILE NOT FOUND"},
        {ERROR_PARAMETER_MISSED, "REQUIRED PARAMETER MISSED"},
        {ERROR_OPEN_HIVE_FAILED, "OPEN REGISTRY HIVE FAILED"},
        {ERROR_CREATE_HIVE_FAILED, "CREATE REGISTRY HIVE FAILED"},
        {ERROR_CREATE_KEY_FAILED, "CREATE REGISTRY KEY FAILED"},
        {ERROR_QUERY_INFO_FAILED, "QUERY INFORMATION FAILED"},
        {ERROR_DELETE_DAT_FAILED, "DELETE DAT FILE FAILED"},
        {ERROR_DELETE_REG_FAILED, "DELETE REG FILE FAILED"},
        {DEBUG_INFO, "DEBUG"},
        {USER_INFO, "INFOR"},
    };
    // get error message according to error number
    std::string get_error_message(int error);
    // print error with error number
    void print_error(int error);
    // print error with error number and different level
    void print_error(int level, int error);
    // print error with error number and different level and detail string
    void print_error(int level, int error, std::string detail);

}