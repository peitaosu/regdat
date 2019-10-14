#include "common.h"

bool file_exists(std::string file_path)
{
    return std::experimental::filesystem::exists(file_path.c_str());
}

std::wstring stringTowstring(std::string str) {
    std::wstring wstr(str.begin(), str.end());
    return wstr;
}

std::string wstringTostring(std::wstring wstr) {
    std::string str(wstr.begin(), wstr.end());
    return str;
}