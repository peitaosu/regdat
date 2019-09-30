#include "RegValue.h"

std::wstring RegValue::get_name()
{
    return this->value_name;
}

std::wstring RegValue::get_data()
{
    return this->value_data;
}

std::wstring RegValue::get_type()
{
    return this->value_type;
}

void RegValue::set_name(std::wstring new_name)
{
    this->value_name = new_name;
}

void RegValue::set_data(std::wstring new_data)
{
    this->value_data = new_data;
}

void RegValue::set_type(std::wstring new_type)
{
    this->value_type = new_type;
}

bool RegValue::operator==(RegValue& obj)
{
    RegValue value;
    if (value.value_name == obj.value_name)
        return true;
    return false;
}
