# regdat

[![GitHub license](https://img.shields.io/github/license/peitaosu/regdat)](https://github.com/peitaosu/regdat/blob/master/LICENSE)
![WDK](https://img.shields.io/badge/WDK-10.0-blue)
![Windows](https://img.shields.io/badge/Windows-7%20%7C%2010-blue.svg)

This is a Registry Hive Tool which supported convert registry files between different types, such as reg and dat.

## dependencies
* offreg (part of WDK)

## build
1. Update the path to `offreg.lib` in `regdat.vcxproj`.
2. Build `regdat.vcxproj`.
3. Copy `offreg.dll` to build output folder.

## supported features
* reg to dat
* dat to reg

## usage
```
Usage:
        regdat.exe --reg2dat --in_reg <path_to_reg_file> --out_dat <path_to_dat_file>
        regdat.exe --dat2reg --in_dat <path_to_dat_file> --out_reg <path_to_reg_file>
```
