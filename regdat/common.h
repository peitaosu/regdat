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

#pragma once
#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <chrono>

namespace regdat {
    // check file existence
    bool file_exists(std::string file_path);
    // delete file
    bool delete_file(std::string file_path);
    // string to wstring
    std::wstring string2wstring(std::string str);
    // wstring to string
    std::string wstring2string(std::wstring wstr);
    // dec int to hex string
    std::string dec2hex(int dec);
    // hex string to dec int
    int hex2dec(std::string hex);
    // get current clock time
    std::chrono::high_resolution_clock::time_point get_current_time();
}
