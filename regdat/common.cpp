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

#include "common.h"

namespace regdat {
    bool file_exists(std::string file_path)
    {
        return std::filesystem::exists(file_path.c_str());
    }

    bool delete_file(std::string file_path)
    {
        return std::filesystem::remove(file_path.c_str());
    }

    std::wstring string2wstring(std::string str) {
        std::wstring wstr(str.begin(), str.end());
        return wstr;
    }

    std::string wstring2string(std::wstring wstr) {
        std::string str(wstr.begin(), wstr.end());
        return str;
    }

    std::string dec2hex(int dec)
    {
        std::stringstream ss;
        ss << std::hex << dec;
        return ss.str();
    }

    int hex2dec(std::string hex)
    {
        std::stringstream ss;
        int dec;
        ss << hex;
        ss >> std::hex >> dec;
        return dec;
    }

    std::chrono::high_resolution_clock::time_point get_current_time()
    {
        return std::chrono::high_resolution_clock::now();
    }
}

