#include "reg2dat.h"
#include <fstream>

int Reg2Dat(std::string in_reg_path, std::string out_dat_path)
{
    if (!file_exists(in_reg_path)) {
        std::cout << in_reg_path << " not exists." << std::endl;
        return -1;
    }
    std::ifstream in_file(in_reg_path);
    std::list<std::string> reg_lines;
    if (in_file.is_open()) {
        std::string line;
        while (std::getline(in_file, line)) {
            line.erase(std::remove_if(line.begin(), line.end(),
                [](char c) { return c =='\0' || c < 0 || c == '\r'; }), line.end());
            reg_lines.push_back(line);
            std::cout << line << std::endl;
        }
        in_file.close();
    }
    ORHKEY off_hive;
    ORCreateHive(&off_hive);
    ORHKEY created_key;
    for (std::list<std::string>::iterator it = reg_lines.begin(); it != reg_lines.end(); ++it) {
        if (it->length() == 0 || (it->at(0) != '@' && it->at(0) != '[' && it->at(0) != '"')) {
            ORCloseKey(created_key);
            continue;
        }
        if (it->at(0) == '['){
            std::string key_string = it->substr(1, it->length() - 2);
            std::wstring key_wstring = stringTowstring(key_string);
            ORCreateKey(off_hive, key_wstring.c_str(), NULL, NULL, NULL, &created_key, NULL);
            continue;
        }
        if (it->at(0) == '@'){
            if (it->at(2) == '"') {
                std::string data = it->substr(3, it->length() - 4);
                ORSetValue(created_key, NULL, REG_SZ, (const BYTE*)data.c_str(), data.size() + 1);
            } else {
                if (it->substr(2, 4) == "hex:") {
                    std::string data = it->substr(6, it->length() - 6);
                    ORSetValue(created_key, NULL, REG_BINARY, (const BYTE*)data.c_str(), data.size() + 1);
                } else {
                    if (it->substr(2, 6) == "dword:") {
                        std::string data = it->substr(8, it->length() - 8);
                        ORSetValue(created_key, NULL, REG_DWORD, (const BYTE*)std::stoi(data), 4);
                    }
                }
            }
            continue;
        }
        if (it->at(0) == '"'){
            //TODO: parse value
        }
    }
    std::wstring out_dat_path_w(out_dat_path.begin(), out_dat_path.end());
    ORSaveHive(off_hive, out_dat_path_w.c_str(), REG_VER_MAJOR, REG_VER_MINOR);
    return 0;
}
