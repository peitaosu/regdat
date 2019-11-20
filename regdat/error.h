#pragma once
#include "common.h"
#include "def.h"
#include <map>

namespace regdat {
    static const std::map<int, std::string> Errors = {
        {SUCCEED, "SUCCEED"},
        {ERROR_REG_FILE_NOT_FOUND, "REG FILE NOT FOUND"},
        {ERROR_DAT_FILE_NOT_FOUND, "DAT FILE NOT FOUND"},
        {ERROR_PARAMETER_MISSED, "REQUIRED PARAMETER MISSED"},
        {ERROR_OPEN_HIVE_FAILED, "OPEN REGISTRY HIVE FAILED"},
        {ERROR_CREATE_HIVE_FAILED, "CREATE REGISTRY HIVE FAILED"},
        {ERROR_CREATE_KEY_FAILED, "CREATE REGISTRY KEY FAILED"},
        {ERROR_QUERY_INFO_FAILED, "QUERY INFORMATION FAILED"},
        {ERROR_DELETE_DAT_FAILED, "DELETE DAT FILE FAILED"},
        {ERROR_DELETE_REG_FAILED, "DELETE REG FILE FAILED"},
    };
    std::string get_error_message(int error);
    void print_error(int error);
    void print_error_detail(int error, std::string detail);
}