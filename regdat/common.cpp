#include "common.h"

bool file_exists(std::wstring file_path)
{
    return std::experimental::filesystem::exists(file_path.c_str());
}
