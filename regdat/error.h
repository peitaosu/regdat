#pragma once
#include "common.h"
#include "def.h"
#include <map>

static const std::map<int, std::string> Errors = {
    {SUCCEED, "Succeed."},
    {ERROR_REG_FILE_NOT_FOUND, ".reg file not found."},
    {ERROR_DAT_FILE_NOT_FOUND, ".dat file not found."},
    {ERROR_PARAMETER_MISSED, "Required parameter missed."},
    {ERROR_OPEN_HIVE_FAILED, "Open registry hive failed."},
    {ERROR_CREATE_HIVE_FAILED, "Create registry hive failed."},
    {ERROR_CREATE_KEY_FAILED, "Create registry key failed."},
    {ERROR_QUERY_INFO_FAILED, "Query information failed."},
    {ERROR_DELETE_DAT_FAILED, "Delete dat file failed."},
    {ERROR_DELETE_REG_FAILED, "Delete reg file failed."},
};
std::string GetErrorMessage(int error);
void PrintErrorMessage(int error);
void PrintErrorMessageWithDetail(int error, std::string detail);
