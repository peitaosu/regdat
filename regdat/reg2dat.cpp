#include "reg2dat.h"
#include "common.h"

namespace regdat {
    int reg2dat(std::string in_reg_path, std::string out_dat_path)
    {
        // print action and input/output for debug
        print_error(2, USER_INFO, "Action Start: reg2dat");
        print_error(2, USER_INFO, "Input: --in_reg " + in_reg_path);
        print_error(2, USER_INFO, "Output: --out_dat " + out_dat_path);
        auto start_time = get_current_time();

        // if input file not exists, return error
        if (!file_exists(in_reg_path)) {
            print_error(0, ERROR_REG_FILE_NOT_FOUND, in_reg_path + " not exists.");
            return ERROR_REG_FILE_NOT_FOUND;
        }

        // read lines from input file
        std::wifstream in_file(in_reg_path);
        std::vector<std::wstring> reg_lines;
        if (in_file.is_open()) {
            std::wstring line;

            // not_ended will set to true if current line is not ended
            bool not_ended = false;
            // not_ended_str is used to store current not ended line and will append with next line
            std::wstring not_ended_str = L"";

            // split lines with "\n" automatically
            while (std::getline(in_file, line)) {
                std::wstring line_str = L"";
                
                // remove \0 and <0 characters
                // if reg file was exported from regedit.exe, it will includes \0 bytes in second char, and \r in end of line, remove them
                for (int i = 0; i < line.length(); i++) {
                    if (line[i] <= 0 || line[i] == '\r') continue;
                    line_str += line[i];
                }

                // empty line
                if (line_str.length() == 0) continue;
                
                // if previous line is not_ended line, append with current line
                if (not_ended) {
                    line_str = not_ended_str + line_str;
                }

                // if \ in the end of line, that means current line is not ended, else is ended
                if (*line_str.rbegin() == '\\') {
                    not_ended = true;
                    not_ended_str = line_str.substr(0, line_str.length() - 1);
                }
                else {
                    not_ended = false;
                    reg_lines.push_back(line_str);
                }
            }
            // close file after reading data done
            in_file.close();
        }

        // create new registry hive, return error if failed
        ORHKEY off_hive;
        if (ORCreateHive(&off_hive) != ERROR_SUCCESS) {
            print_error(0, ERROR_CREATE_HIVE_FAILED, "Cannot create hive, error code: " + GetLastError());
            return ERROR_CREATE_HIVE_FAILED;
        }

        // created_key is registry pointer, will be set to root when want to create registry key with full path
        ORHKEY created_key = off_hive;
        for (std::wstring reg_line : reg_lines) {
            
            // empty line or invalid line 
            if (reg_line.length() == 0 || (reg_line.at(0) != '@' && reg_line.at(0) != '[' && reg_line.at(0) != '"')) {
                continue;
            }

            // registry key line
            if (reg_line.at(0) == '['){
                created_key = off_hive;
                std::wstring key_string = reg_line.substr(1, reg_line.length() - 2);
                print_error(2, DEBUG_INFO, "Processing Registry Key " + wstring2string(key_string));
                std::wistringstream is(key_string);
                std::wstring next_key_name;
            
                // create registry key with full path, return error when failed
                while (std::getline(is, next_key_name, L'\\')) {
                    if (ORCreateKey(created_key, next_key_name.c_str(), NULL, REG_OPTION_NON_VOLATILE, NULL, &created_key, NULL) != ERROR_SUCCESS) {
                        print_error(0, ERROR_CREATE_KEY_FAILED, "Cannot create key: " + wstring2string(next_key_name));
                        return ERROR_CREATE_KEY_FAILED;
                    }
                }
                continue;
            }

            // registry value line
            std::wstring value_name_string = reg_line.substr(0, reg_line.find('='));
            std::wstring value_data_string = reg_line.substr(reg_line.find('=') + 1, reg_line.length() - reg_line.find('=') - 1);
            LPCWSTR value_name = NULL;
            
            // if value name is @, that means default value
            if (value_name_string != L"@") {
                value_name_string = value_name_string.substr(1, value_name_string.length() - 2);
                value_name = value_name_string.c_str();
            }

            // REG_SZ
            if (value_data_string.at(0) == '"') {
                std::wstring value_data = value_data_string.substr(1, value_data_string.length() - 2);
                ORSetValue(created_key, value_name, REG_SZ, (LPBYTE)value_data.c_str(), (DWORD)((value_data.size() + 1) * sizeof(wchar_t)));
                continue;
            }

            // REG_DWORD
            if (value_data_string.substr(0, 6) == L"dword:") {
                std::wstring value_data = value_data_string.substr(6, value_data_string.length() - 6);
                // in reg file, dword is hex string
                DWORD value = std::stoul(value_data, 0, 16);
                ORSetValue(created_key, value_name, REG_DWORD, (LPBYTE)&value, sizeof(value));
                continue;
            }

            // REG_BINARY
            if (value_data_string.substr(0, 4) == L"hex:") {
                std::wstring value_data = value_data_string.substr(4, value_data_string.length() - 4);
                std::wistringstream is(value_data);
                std::wstring next_char;
                std::string data;
                // in reg file, binary data is hex string and delimiter is ,
                while (std::getline(is, next_char, L',')) {
                    data += std::stoi(next_char, 0, 16);
                }
                ORSetValue(created_key, value_name, REG_BINARY, (LPBYTE)data.c_str(), (DWORD)data.size());
                continue;
            }

            // REG_EXPAND_SZ
            if (value_data_string.substr(0, 7) == L"hex(2):") {
                std::wstring value_data = value_data_string.substr(7, value_data_string.length() - 7);
                std::wistringstream is(value_data);
                std::wstring next_char;
                std::wstring data;
                // in reg file, expand string is hex string with 00 for second char and delimiter is ,
                while (std::getline(is, next_char, L',')) {
                    if (next_char == L"00") continue;
                    data += std::stoi(next_char, 0, 16);
                }
                ORSetValue(created_key, value_name, REG_EXPAND_SZ, (LPBYTE)data.c_str(), (DWORD)((data.size() + 1) * sizeof(wchar_t)));
                continue;
            }

            // REG_MULTI_SZ
            if (value_data_string.substr(0, 7) == L"hex(7):") {
                std::wstring value_data = value_data_string.substr(7, value_data_string.length() - 7);
                std::wistringstream is(value_data);
                std::wstring next_char;
                std::vector<int> dataArray;
                // in reg file, multiple lines string is hex string with 00 for second char and delimiter is ,
                while (std::getline(is, next_char, L',')) {
                    dataArray.push_back(std::stoi(next_char, 0, 16));
                }
                std::wstring data;
                for (int i = 0; i < dataArray.size(); i += 2) {
                    data += dataArray[i];
                }
                ORSetValue(created_key, value_name, REG_MULTI_SZ, (LPBYTE)data.c_str(), (DWORD)((data.size() + 1) * sizeof(wchar_t)));
                continue;
            }

            // REG_QWORD
            if (value_data_string.substr(0, 7) == L"hex(b):") {
                std::wstring value_data = value_data_string.substr(7, value_data_string.length() - 7);
                std::wistringstream is(value_data);
                std::wstring next_char;
                std::wstring data;
                while (std::getline(is, next_char, L',')) {
                    data = next_char + data;
                }
                // QWORD is unsigned long long
                unsigned long long q_data = std::stoull(data, 0, 16);
                ORSetValue(created_key, value_name, REG_QWORD, (LPBYTE)&q_data, sizeof(q_data));
                continue;
            }
        }
        
        std::wstring out_dat_path_w = string2wstring(out_dat_path);
        // if output file is exists, delete it
        if (file_exists(out_dat_path)) {
            // return error if failed
            if (!delete_file(out_dat_path)) {
                print_error(0, ERROR_DELETE_DAT_FAILED, out_dat_path);
                ORCloseHive(off_hive);
                return ERROR_DELETE_DAT_FAILED;
            }
        }
        // save hive to file and close
        ORSaveHive(off_hive, out_dat_path_w.c_str(), REG_VER_MAJOR, REG_VER_MINOR);
        ORCloseHive(off_hive);

        // print end info and execution time
        auto end_time = get_current_time();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        print_error(2, USER_INFO, "Execution Time: " + std::to_string(duration) + " microseconds");
        print_error(2, USER_INFO, "Action Completed: reg2dat");

        return SUCCEED;
    }

    int enumerate_keys(ORHKEY off_key, std::wstring key_name, std::vector<std::wstring>& reg_lines)
    {
    

        // get count of subkeys and values
        DWORD sub_keys_count, values_count;
        if (ORQueryInfoKey(off_key, NULL, NULL, &sub_keys_count, NULL, NULL, &values_count, NULL, NULL, NULL, NULL) != ERROR_SUCCESS)
            return ERROR_QUERY_INFO_FAILED;

        if (values_count > 0) {
            // create registry key line
            if (key_name != L"") {
                print_error(2, DEBUG_INFO, "Processing Registry Key " + wstring2string(key_name));
                std::wstring key_name_string = L"[" + key_name + L"]";
                reg_lines.push_back(L"");
                reg_lines.push_back(key_name_string);
            }

            // enumerate all values
            for (DWORD i = 0; i < values_count; i++) {
                WCHAR value[MAX_REG_VALUE_NAME_SIZE];
                memset(value, 0, sizeof(value));
                DWORD size = MAX_REG_VALUE_NAME_SIZE;
                DWORD type = 0;
                DWORD data_len = 0;

                // get value data length
                if (OREnumValue(off_key, i, value, &size, &type, NULL, &data_len) != ERROR_MORE_DATA)
                    continue;

                LPBYTE data = new BYTE[data_len + 2];
                if (!data) continue;
                memset(data, 0, data_len + 2);

                // get value data
                if (OREnumValue(off_key, i, value, &size, &type, data, &data_len) != ERROR_SUCCESS)
                {
                    delete[] data;
                    continue;
                }

                // @ for default value
                std::wstring value_name = L"@";
                if (std::wstring(value) != L"") {
                    value_name = L"\"" + std::wstring(value) + L"\"";
                }
                // REG_DWORD
                if (type == REG_DWORD) {
                    std::wstring value_data = L"";
                    for (int index = int(data_len - 1); index >= 0; index--) {
                        value_data += (data[index] > 15 ? string2wstring(dec2hex(data[index])) : L"0" + string2wstring(dec2hex(data[index])));
                    }
                    reg_lines.push_back(value_name + L"=dword:" + value_data);
                    delete[] data;
                    continue;
                }

                // REG_SZ
                if (type == REG_SZ) {
                    std::wstring value_data = L"";
                    for (int index = 0; index < int(data_len - 2); index = index + 2) value_data += data[index];
                    reg_lines.push_back(value_name + L"=\"" + value_data + L"\"");
                    delete[] data;
                    continue;
                }

                // REG_BINARY
                if (type == REG_BINARY) {
                    std::wstring value_data = L"";
                    for (int index = 0; index < int(data_len); index++) {
                        value_data += (data[index] > 15 ? string2wstring(dec2hex(data[index])) : L"0" + string2wstring(dec2hex(data[index])));
                        if (index != int(data_len - 1)) value_data += L",";
                    }
                    reg_lines.push_back(value_name + L"=hex:" + value_data);
                    delete[] data;
                    continue;
                }

                // REG_QWORD
                if (type == REG_QWORD) {
                    std::wstring value_data = L"";
                    for (int index = 0; index < int(data_len); index++) {
                        value_data += (data[index] > 15 ? string2wstring(dec2hex(data[index])) : L"0" + string2wstring(dec2hex(data[index])));
                        if (index != int(data_len) - 1) value_data += L",";
                    }
                    reg_lines.push_back(value_name + L"=hex(b):" + value_data);
                    delete[] data;
                    continue;
                }

                // REG_MULTI_SZ
                if (type == REG_MULTI_SZ) {
                    std::wstring value_data = L"";
                    for (int index = 0; index < int(data_len - 2); index = index + 2) {
                        value_data += (data[index] > 15 ? string2wstring(dec2hex(data[index])) : L"0" + string2wstring(dec2hex(data[index]))) + L",00";
                        if (index != int(data_len - 2) - 2) value_data += L",";
                    }
                    value_data += L",00,00";
                    reg_lines.push_back(value_name + L"=hex(7):" + value_data);
                    delete[] data;
                    continue;
                }

                // REG_EXPAND_SZ
                if (type == REG_EXPAND_SZ) {
                    std::wstring value_data = L"";
                    for (int index = 0; index < int(data_len - 2); index = index + 2) {
                        value_data += (data[index] > 15 ? string2wstring(dec2hex(data[index])) : L"0" + string2wstring(dec2hex(data[index]))) + L",00";
                        if (index != int(data_len - 2) - 2) value_data += L",";
                    }
                    value_data += L",00,00";
                    reg_lines.push_back(value_name + L"=hex(2):" + value_data);
                    delete[] data;
                    continue;
                }
            }
        }

        // enumerate all subkeys
        for (DWORD i = 0; i < sub_keys_count; i++) {
            WCHAR sub_key[MAX_REG_KEY_NAME_SIZE];
            memset(sub_key, 0, sizeof(sub_key));
            DWORD size = MAX_REG_KEY_NAME_SIZE;

            // get next key name
            if (OREnumKey(off_key, i, sub_key, &size, NULL, NULL, NULL) != ERROR_SUCCESS)
                continue;

            // get next key full path
            std::wstring next_key;
            if (key_name != L"") {
                next_key = key_name + L"\\" + std::wstring(sub_key);
            }
            else {
                next_key = std::wstring(sub_key);
            }
        
            // enumerate next key, close after done
            ORHKEY off_key_next;
            if (OROpenKey(off_key, sub_key, &off_key_next) == ERROR_SUCCESS)
            {
                enumerate_keys(off_key_next, next_key, reg_lines);
                ORCloseKey(off_key_next);
            }
        }
        return SUCCEED;
    }

    int dat2reg(std::string in_dat_path, std::string out_reg_path) {

        // print action and input/output for debug
        print_error(2, USER_INFO, "Action Start: dat2reg");
        print_error(2, USER_INFO, "Input: --in_dat " + in_dat_path);
        print_error(2, USER_INFO, "Output: --out_reg " + out_reg_path);
        auto start_time = get_current_time();

        // if input file not exists, return error
        if (!file_exists(in_dat_path)) {
            print_error(0, ERROR_DAT_FILE_NOT_FOUND, in_dat_path + " not exists.");
            return ERROR_DAT_FILE_NOT_FOUND;
        }
        std::wstring in_dat_path_w = string2wstring(in_dat_path);

        // open registry hive, get, parse data and write to string lines 
        ORHKEY off_hive;
        std::vector<std::wstring> reg_lines;
        OROpenHive(in_dat_path_w.c_str(), &off_hive);
        // first line is regedit version string
        reg_lines.push_back(REG_VER_STRING);
        // enumerate_keys from root
        enumerate_keys(off_hive, L"", reg_lines);

        // if output file is exists, delete it
        if (file_exists(out_reg_path)) {
            // return error if failed
            if (!delete_file(out_reg_path)) {
                print_error(0, ERROR_DELETE_REG_FAILED, out_reg_path);
                ORCloseHive(off_hive);
                return ERROR_DELETE_REG_FAILED;
            }
        }

        // write string lines to file, end with \n each line
        std::wofstream out_file(string2wstring(out_reg_path));
        for (std::wstring reg_line : reg_lines)
            out_file << reg_line << "\n";

        // close file
        out_file.close();

        // close registry hive
        ORCloseHive(off_hive);

        // print end info and execution time
        auto end_time = get_current_time();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        print_error(2, USER_INFO, "Execution Time: " + std::to_string(duration) + " microseconds");
        print_error(2, USER_INFO, "Action Completed: dat2reg");

        return SUCCEED;
    }
}