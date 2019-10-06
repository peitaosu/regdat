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
    if (opts.check("--reg2dat")) {
        if (!opts.check("--in_reg")) {
            std::wcout << "--in_reg is required." << std::endl;
            return -1;
        }
        if (!opts.check("--out_dat")) {
            std::wcout << "--out_dat is required." << std::endl;
            return -1;
        }
        Reg2Dat(opts.get_value("--in_reg"), opts.get_value("--out_dat"));
    }
}
