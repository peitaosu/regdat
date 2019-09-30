#pragma once
#include <string>
#include <list>
#include "RegValue.h"

class RegKey
{
public:
    std::wstring get_name();
    std::wstring get_path();
    RegKey get_subkey(std::wstring key_name);
    int add_subkey(RegKey subkey);
    int remove_subkey(std::wstring key_name);
    RegValue get_value(std::wstring value_name);
    int add_value(RegValue value);
    int remove_value(std::wstring value_name);
    bool operator==(RegKey& obj);

private:
    std::wstring key_path;
    std::wstring key_name;
    std::list<RegKey> sub_keys;
    std::list<RegValue> values;
};

