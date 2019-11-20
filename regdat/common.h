#pragma once
#include <iostream>
#include <filesystem>
#include <sstream>

namespace regdat {
    bool file_exists(std::string file_path);
    bool delete_file(std::string file_path);
    std::wstring string2wstring(std::string str);
    std::string wstring2string(std::wstring wstr);
    std::string dec2hex(int dec);
    int hex2dec(std::string hex);
}
