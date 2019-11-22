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

#ifndef MAX_REG_KEY_NAME_SIZE
#define MAX_REG_KEY_NAME_SIZE      255
#endif // !MAX_REG_KEY_NAME_SIZE

#ifndef MAX_REG_VALUE_NAME_SIZE
#define MAX_REG_VALUE_NAME_SIZE    16383
#endif // !MAX_REG_VALUE_NAME_SIZE

#ifndef MAX_REG_VALUE_DATA_SIZE
#define MAX_REG_VALUE_DATA_SIZE    1024000
#endif // !MAX_REG_VALUE_DATA_SIZE

#ifndef REG_VER_MAJOR
#define REG_VER_MAJOR              6
#endif // !REG_VER_MAJOR

#ifndef REG_VER_MINOR
#define REG_VER_MINOR              1
#endif // !REG_VER_MINOR

#ifndef REG_VER_STRING
#define REG_VER_STRING             L"Windows Registry Editor Version 5.00"
#endif // !REG_VER_STRING

#ifndef SUCCEED
#define SUCCEED                    0
#endif // !SECCEED

#ifndef DEBUG_INFO
#define DEBUG_INFO                 1
#endif // !DEBUG_INFO

#ifndef USER_INFO
#define USER_INFO                  2
#endif // !USER_INFO

#ifndef ERROR_REG_FILE_NOT_FOUND
#define ERROR_REG_FILE_NOT_FOUND   -1
#endif // !ERROR_REG_FILE_NOT_FOUND

#ifndef ERROR_DAT_FILE_NOT_FOUND
#define ERROR_DAT_FILE_NOT_FOUND   -2
#endif // !ERROR_DAT_FILE_NOT_FOUND

#ifndef ERROR_PARAMETER_MISSED
#define ERROR_PARAMETER_MISSED     -3
#endif // !ERROR_PARAMETER_MISSED

#ifndef ERROR_OPEN_HIVE_FAILED
#define ERROR_OPEN_HIVE_FAILED     -11
#endif // !ERROR_OPEN_HIVE_FAILED

#ifndef ERROR_CREATE_HIVE_FAILED
#define ERROR_CREATE_HIVE_FAILED   -12
#endif // !ERROR_CREATE_HIVE_FAILEF

#ifndef ERROR_CREATE_KEY_FAILED
#define ERROR_CREATE_KEY_FAILED    -13
#endif // !ERROR_CREATE_KEY_FAILED

#ifndef ERROR_QUERY_INFO_FAILED
#define ERROR_QUERY_INFO_FAILED    -14
#endif // !ERROR_QUERY_INFO_FAILED

#ifndef ERROR_DELETE_DAT_FAILED
#define ERROR_DELETE_DAT_FAILED    -21
#endif // !ERROR_DELETE_DAT_FAILED

#ifndef ERROR_DELETE_REG_FAILED
#define ERROR_DELETE_REG_FAILED    -22
#endif // !ERROR_DELETE_REG_FAILED


