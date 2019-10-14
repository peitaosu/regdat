#pragma once
#include <iostream>
#include <filesystem>

bool file_exists(std::string file_path);
std::wstring stringTowstring(std::string str);
std::string wstringTostring(std::wstring wstr);