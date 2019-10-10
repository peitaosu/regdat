#include "reg2dat.h"
#include <fstream>

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
            reg_lines.push_back(line);
        }
        in_file.close();
    }
    ORHKEY off_hive;
    ORCreateHive(&off_hive);
    for (std::list<std::wstring>::iterator it = reg_lines.begin(); it != reg_lines.end(); ++it) {
        if (it->at(0) == '['){
            //TODO: parse key
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
        if (it->find(L"Windows Registry Editor Version 5.00") == 0)
            continue;
    }
    std::wstring out_dat_path_w(out_dat_path.begin(), out_dat_path.end());
    ORSaveHive(off_hive, out_dat_path_w.c_str(), REG_VER_MAJOR, REG_VER_MINOR);
    return 0;
}
