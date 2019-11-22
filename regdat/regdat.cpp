// MIT License
//
// Copyright (c) 2019 Tony Su
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
