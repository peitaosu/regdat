#pragma once
#include <iostream>
#include <Windows.h>
#include <offreg.h>
#include "def.h"
#include "common.h"
#include "error.h"

namespace regdat {
    int reg2dat(std::string in_reg_path, std::string out_dat_path);
    int dat2reg(std::string in_dat_path, std::string out_reg_path);
    int enumerate_keys(ORHKEY OffKey, std::wstring szKeyName, std::vector<std::wstring>& reg_lines);
}
