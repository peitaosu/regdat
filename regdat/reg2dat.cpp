#include "reg2dat.h"
#include <fstream>
#include <sstream>

int Reg2Dat(std::string in_reg_path, std::string out_dat_path)
{
    if (!file_exists(in_reg_path)) {
        std::cout << in_reg_path << " not exists." << std::endl;
        return ERROR_REG_FILE_NOT_FOUND;
    }
    std::wifstream in_file(in_reg_path);
    std::vector<std::wstring> reg_lines;
    if (in_file.is_open()) {
        std::wstring line;
        while (std::getline(in_file, line)) {
            std::wstring line_str = L"";
            for (int i = 0; i < line.length(); i++) {
                // remove \0 and <0 characters
                if (line[i] <= 0 || line[i] == '\r') continue;
                line_str += line[i];
            }
            reg_lines.push_back(line_str);
        }
        in_file.close();
    }
    ORHKEY off_hive;
    if (ORCreateHive(&off_hive) != ERROR_SUCCESS) {
        std::wcout << "[ERROR]: Cannot create hive: " << GetLastError() << std::endl;
        return ERROR_CREATE_HIVE_FAILED;
    }
    ORHKEY created_key = off_hive;
    for (std::wstring reg_line : reg_lines) {
        if (reg_line.length() == 0 || (reg_line.at(0) != '@' && reg_line.at(0) != '[' && reg_line.at(0) != '"')) {
            continue;
        }
        if (reg_line.at(0) == '['){
            std::wstring key_string = reg_line.substr(1, reg_line.length() - 2);
            std::wistringstream is(key_string);
            std::wstring next_key_name;
            while (std::getline(is, next_key_name, L'\\')) {
                if (ORCreateKey(created_key, next_key_name.c_str(), NULL, REG_OPTION_NON_VOLATILE, NULL, &created_key, NULL) != ERROR_SUCCESS) {
                    std::wcout << "[ERROR]: Cannot create key: " << next_key_name << " error code: " << GetLastError() << std::endl;
                    return ERROR_CREATE_KEY_FAILED;
                }
            }
            continue;
        }
        std::wstring value_name_string = reg_line.substr(0, reg_line.find('='));
        std::wstring value_data_string = reg_line.substr(reg_line.find('=') + 1, reg_line.length() - reg_line.find('=') - 1);
        LPCWSTR value_name = NULL;
        if (value_name_string != L"@") {
            value_name_string = value_name_string.substr(1, value_name_string.length() - 2);
            value_name = value_name_string.c_str();
        }
        if (value_data_string.at(0) == '"') {
            std::wstring value_data = value_data_string.substr(1, value_data_string.length() - 2);
            ORSetValue(created_key, value_name, REG_SZ, (LPBYTE)value_data.c_str(), sizeof(value_data));
            continue;
        }
        if (value_data_string.substr(0, 6) == L"dword:") {
            std::wstring value_data = value_data_string.substr(6, value_data_string.length() - 6);
            DWORD value = std::stoi(value_data, 0, 16);
            ORSetValue(created_key, value_name, REG_DWORD, (LPBYTE)&value, sizeof(value));
            continue;
        }
        if (value_data_string.substr(0, 4) == L"hex:") {
            std::wstring value_data = value_data_string.substr(4, value_data_string.length() - 4);
            std::wistringstream is(value_data);
            std::wstring next_char;
            std::string data;
            while (std::getline(is, next_char, L',')) {
                data += std::stoi(next_char, 0, 16);
            }
            ORSetValue(created_key, value_name, REG_BINARY, (LPBYTE)data.c_str(), (DWORD)data.size());
            continue;
        }
        if (value_data_string.substr(0, 7) == L"hex(2):") {
            std::wstring value_data = value_data_string.substr(7, value_data_string.length() - 7);
            std::wistringstream is(value_data);
            std::wstring next_char;
            std::wstring data;
            while (std::getline(is, next_char, L',')) {
                if (next_char == L"00") continue;
                data += std::stoi(next_char, 0, 16);
            }
            ORSetValue(created_key, value_name, REG_EXPAND_SZ, (LPBYTE)data.c_str(), sizeof(data));
            continue;
        }
        if (value_data_string.substr(0, 7) == L"hex(7):") {
            //TODO: Multi-Stings
            continue;
        }
        if (value_data_string.substr(0, 7) == L"hex(b):") {
            std::wstring value_data = value_data_string.substr(7, value_data_string.length() - 7);
            std::wistringstream is(value_data);
            std::wstring next_char;
            std::wstring data;
            while (std::getline(is, next_char, L',')) {
                data = next_char + data;
            }
            unsigned long long q_data = std::stoi(data, 0, 16);
            ORSetValue(created_key, value_name, REG_QWORD, (LPBYTE)&q_data, sizeof(q_data));
            continue;
        }
    }
    std::wstring out_dat_path_w(out_dat_path.begin(), out_dat_path.end());
    if (file_exists(out_dat_path)) {
        delete_file(out_dat_path);
    }
    ORSaveHive(off_hive, out_dat_path_w.c_str(), REG_VER_MAJOR, REG_VER_MINOR);
    ORCloseHive(off_hive);
    return SUCCEED;
}
