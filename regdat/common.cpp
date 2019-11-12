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

std::string hex2string(std::string hex)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = hex.length();

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = hex[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        char b = hex[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}

std::string string2hex(std::string string)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = string.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = string[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}