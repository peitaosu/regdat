#include "reg2dat.h"
#include <fstream>
#include <sstream>

int Reg2Dat(std::string in_reg_path, std::string out_dat_path)
{
    if (!file_exists(in_reg_path)) {
        std::cout << in_reg_path << " not exists." << std::endl;
        return -1;
    }
    std::wifstream in_file(in_reg_path);
    std::list<std::wstring> reg_lines;
    if (in_file.is_open()) {
        std::wstring line;
        while (std::getline(in_file, line)) {
            line.erase(std::remove_if(line.begin(), line.end(),
                [](char c) { return c =='\0' || c < 0 || c == '\r'; }), line.end());
            reg_lines.push_back(line);
            std::wcout << line << std::endl;
        }
        in_file.close();
    }
    ORHKEY off_hive;
    if (ORCreateHive(&off_hive) != ERROR_SUCCESS) {
        std::wcout << "[ERROR]: Cannot create hive: " << GetLastError() << std::endl;
        return -1;
    }
    ORHKEY created_key = off_hive;
    for (std::list<std::wstring>::iterator it = reg_lines.begin(); it != reg_lines.end(); ++it) {
        if (it->length() == 0 || (it->at(0) != '@' && it->at(0) != '[' && it->at(0) != '"')) {
            continue;
        }
        if (it->at(0) == '['){
            std::wstring key_string = it->substr(1, it->length() - 2);
            std::wistringstream is(key_string);
            std::wstring next_key_name;
            while (std::getline(is, next_key_name, L'\\')) {
                if (ORCreateKey(created_key, next_key_name.c_str(), NULL, REG_OPTION_NON_VOLATILE, NULL, &created_key, NULL) != ERROR_SUCCESS) {
                    std::wcout << "[ERROR]: Cannot create key: " << next_key_name << " error code: " << GetLastError() << std::endl;
                    return -1;
                }
            }
            continue;
        }
        std::wstring value_name_string = it->substr(0, it->find('=') - 1);
        std::wstring value_data_string = it->substr(it->find('=') + 1, it->length() - it->find('=') - 1);
        LPCWSTR value_name = NULL;
        if (value_name_string != L"@") {
            value_name = value_name_string.substr(1, value_name_string.length() - 2).c_str();
        }
        if (value_data_string.at(0) == '"') {
            std::wstring value_data = value_data_string.substr(1, value_data_string.length() - 2);
            ORSetValue(created_key, value_name, REG_SZ, (LPBYTE)value_data.c_str(), (value_data.size() + 1) * sizeof(wchar_t));
            continue;
        }
        if (value_data_string.substr(0, 6) == L"dword:") {
            std::wstring value_data = value_data_string.substr(8, value_data_string.length() - 8);
            DWORD value = std::stoi(value_data, 0, 16);
            ORSetValue(created_key, value_name, REG_DWORD, (LPBYTE)&value, sizeof(value));
            continue;
        }
        if (value_data_string.substr(0, 4) == L"hex:") {
            std::wstring value_data = value_data_string.substr(6, value_data_string.length() - 6);
            std::wstring data = string2wstring(hex2string(wstring2string(value_data)));
            ORSetValue(created_key, value_name, REG_BINARY, (LPBYTE)data.c_str(), (data.size() + 1) * sizeof(wchar_t));
            continue;
        }
        if (value_data_string.substr(0, 7) == L"hex(2):") {
            //TODO: Expand String
            continue;
        }
        if (value_data_string.substr(0, 7) == L"hex(7):") {
            //TODO: Multi-Stings
            continue;
        }
        if (value_data_string.substr(0, 7) == L"hex(b):") {
            //TODO: QWORD
            continue;
        }
    }
    std::wstring out_dat_path_w(out_dat_path.begin(), out_dat_path.end());
    ORSaveHive(off_hive, out_dat_path_w.c_str(), REG_VER_MAJOR, REG_VER_MINOR);
    ORCloseHive(off_hive);
    return 0;
}
