// regdat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <offreg.h>

int main()
{
    ORHKEY off_hive;
    PCWSTR reg_file = L"registry.dat";
    if (OROpenHive(reg_file, &off_hive) != ERROR_SUCCESS)
    {
        std::cout << "[ERROR] Cannot open hive file: " << reg_file << std::endl;
        return -1;
    }
}
