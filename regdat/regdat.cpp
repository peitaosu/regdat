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
    // if not supported action in parameters, print usage
    if (!opts.check("--reg2dat") && !opts.check("--dat2reg")) {
        std::cout << "Usage:\n\tregdat.exe --reg2dat --in_reg <path_to_reg_file> --out_dat <path_to_dat_file>\n\tregdat.exe --dat2reg --in_dat <path_to_dat_file> --out_reg <path_to_reg_file>" << std::endl;
        return SUCCEED;
    }
    // reg2dat, return error if required parameters missed
    if (opts.check("--reg2dat")) {
        if (!opts.check("--in_reg")) {
            regdat::print_error(0, ERROR_PARAMETER_MISSED, "--in_reg is required.");
            return ERROR_PARAMETER_MISSED;
        }
        if (!opts.check("--out_dat")) {
            regdat::print_error(0, ERROR_PARAMETER_MISSED, "--out_dat is required.");
            return ERROR_PARAMETER_MISSED;
        }
        return regdat::reg2dat(opts.get_value("--in_reg"), opts.get_value("--out_dat"));
    }
    // dat2reg, return error if required parameters missed
    if (opts.check("--dat2reg")) {
        if (!opts.check("--in_dat")) {
            regdat::print_error(0, ERROR_PARAMETER_MISSED, "--in_dat is required.");
            return ERROR_PARAMETER_MISSED;
        }
        if (!opts.check("--out_reg")) {
            regdat::print_error(0, ERROR_PARAMETER_MISSED, "--out_reg is required.");
            return ERROR_PARAMETER_MISSED;
        }
        return regdat::dat2reg(opts.get_value("--in_dat"), opts.get_value("--out_reg"));
    }
    return SUCCEED;
}
