#pragma once
#include <iostream>
#include <filesystem>
#include <sstream>

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
}
