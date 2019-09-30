#include "RegKey.h"

std::wstring RegKey::get_name()
{
    return this->key_name;
}

std::wstring RegKey::get_path()
{
    return this->key_path;
}

RegKey RegKey::get_subkey(std::wstring key_name) {
    for (std::list<RegKey>::iterator it = this->sub_keys.begin(); it != this->sub_keys.end(); ++it) {
        if (it->get_name() == key_name)
            return *it;
    }
}

int RegKey::add_subkey(RegKey subkey) {
    for (std::list<RegKey>::iterator it = this->sub_keys.begin(); it != this->sub_keys.end(); ++it) {
        if (it->get_name() == subkey.get_name())
            return -1;
    }
    this->sub_keys.push_back(subkey);
    return 0;
}

int RegKey::remove_subkey(std::wstring key_name) {
    for (std::list<RegKey>::iterator it = this->sub_keys.begin(); it != this->sub_keys.end(); ++it) {
        if (it->get_name() == key_name)
            this->sub_keys.erase(it);
            return 0;
    }
    return -1;
}

RegValue RegKey::get_value(std::wstring value_name) {
    for (std::list<RegValue>::iterator it = this->values.begin(); it != this->values.end(); ++it) {
        if (it->get_name() == value_name)
            return *it;
    }
}

int RegKey::add_value(RegValue value) {
    for (std::list<RegValue>::iterator it = this->values.begin(); it != this->values.end(); ++it) {
        if (it->get_name() == value.get_name())
            return -1;
    }
    this->values.push_back(value);
    return 0;
}

int RegKey::remove_value(std::wstring value_name) {
    for (std::list<RegValue>::iterator it = this->values.begin(); it != this->values.end(); ++it) {
        if (it->get_name() == value_name)
            this->values.erase(it);
            return 0;
    }
    return -1;
}

bool RegKey::operator==(RegKey& obj)
{
    RegKey key;
    if (key.key_path == obj.key_path)
        return true;
    return false;
}

