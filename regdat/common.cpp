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
