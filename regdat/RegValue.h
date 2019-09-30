#pragma once
#include <string>
#include <list>

class RegValue
{
public:
    std::wstring get_name();
    std::wstring get_data();
    std::wstring get_type();
    void set_name(std::wstring new_name);
    void set_data(std::wstring new_data);
    void set_type(std::wstring new_type);
    bool operator==(RegValue& obj);

private:
    std::wstring value_name;
    std::wstring value_data;
    std::wstring value_type;
};
