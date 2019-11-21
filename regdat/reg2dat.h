#pragma once
#include <iostream>
#include <Windows.h>
#include <offreg.h>
#include "def.h"
#include "common.h"
#include "error.h"

namespace regdat {
    // reg to dat
    int reg2dat(std::string in_reg_path, std::string out_dat_path);
    // dat to reg
    int dat2reg(std::string in_dat_path, std::string out_reg_path);
    // function for subkey enumeration
    int enumerate_keys(ORHKEY OffKey, std::wstring szKeyName, std::vector<std::wstring>& reg_lines);
}
