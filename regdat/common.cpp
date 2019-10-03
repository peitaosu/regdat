#include "common.h"

bool file_exists(std::string file_path)
{
    return std::experimental::filesystem::exists(file_path.c_str());
}
