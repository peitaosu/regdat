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
    for (std::list<std::string>::iterator it = reg_lines.begin(); it != reg_lines.end(); ++it) {
        if (it->length() == 0) {
            continue;
        }
        if (it->at(0) == '['){
            std::list<std::string> keys;
            std::string key_string = it->substr(1, it->length() - 2);
            std::string delimiter = "\\";
            size_t pos = 0;
            std::string token;
            while ((pos = key_string.find(delimiter)) != std::string::npos) {
                token = key_string.substr(0, pos);
                keys.push_back(token);
                key_string.erase(0, pos + delimiter.length());
            }
            keys.push_back(key_string);
            //TODO: parse keys
            continue;
        }
        if (it->at(0) == '@'){
            //TODO: parse default value
            continue;
        }
        if (it->at(0) == '"'){
            //TODO: parse value
        }
        if (it->at(0) == ' ')
            continue;
        if (it->find("Windows Registry Editor Version 5.00") == 0)
            continue;
    }
    std::wstring out_dat_path_w(out_dat_path.begin(), out_dat_path.end());
    ORSaveHive(off_hive, out_dat_path_w.c_str(), REG_VER_MAJOR, REG_VER_MINOR);
    return 0;
}
