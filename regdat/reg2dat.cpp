#include "reg2dat.h"
#include <fstream>

int Reg2Dat(std::string in_reg_path, std::string out_dat_path)
{
    if (file_exists(in_reg_path)) {
        std::cout << in_reg_path << " not exists." << std::endl;
        return -1;
    }
    std::wifstream in_file(in_reg_path);
    std::list<std::wstring> reg_lines;
    if (in_file.is_open()) {
        std::wstring line;
        while (getline(in_file, line)) {
            reg_lines.push_back(line);
        }
        in_file.close();
    }
    //TODO: parse reg lines and create registry hive
    ORHKEY off_hive;
    ORCreateHive(&off_hive);
    std::wstring out_dat_path_w(out_dat_path.begin(), out_dat_path.end());
    ORSaveHive(off_hive, out_dat_path_w.c_str(), REG_VER_MAJOR, REG_VER_MINOR);
    return 0;
}
