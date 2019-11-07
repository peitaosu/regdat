// regdat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "def.h"
#include "common.h"
#include "Options.h"
#include "reg2dat.h"

int main(int argc, char **argv)
{
    Options opts(argc, argv);
    if (opts.check("--help") || opts.check("-h")) {
        std::wcout << "Usage:\n\tregdat.exe --in_reg <path_to_reg_file> --out_dat <path_to_dat_file>\n\tregdat.exe -h\\--help" << std::endl;
        return SUCCEED;
    }
    if (opts.check("--reg2dat")) {
        if (!opts.check("--in_reg")) {
            std::wcout << "--in_reg is required." << std::endl;
            return ERROR_PARAMETER_MISSED;
        }
        if (!opts.check("--out_dat")) {
            std::wcout << "--out_dat is required." << std::endl;
            return ERROR_PARAMETER_MISSED;
        }
        return Reg2Dat(opts.get_value("--in_reg"), opts.get_value("--out_dat"));
    }
}
