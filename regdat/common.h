#pragma once
#include <iostream>
#include <filesystem>

bool file_exists(std::string file_path);
bool delete_file(std::string file_path);
std::wstring string2wstring(std::string str);
std::string wstring2string(std::wstring wstr);

