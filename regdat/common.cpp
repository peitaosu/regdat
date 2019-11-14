#include "common.h"

bool file_exists(std::string file_path)
{
    return std::experimental::filesystem::exists(file_path.c_str());
}

bool delete_file(std::string file_path)
{
    return std::experimental::filesystem::remove(file_path.c_str());
}

std::wstring string2wstring(std::string str) {
    std::wstring wstr(str.begin(), str.end());
    return wstr;
}

std::string wstring2string(std::wstring wstr) {
    std::string str(wstr.begin(), wstr.end());
    return str;
}
