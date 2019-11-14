#include "error.h"

std::string GetErrorMessage(int error)
{
    return Errors.find(error)->second;
}

void PrintErrorMessage(int error)
{
    std::cout << "[Error] " << GetErrorMessage(error) << std::endl;
}

void PrintErrorMessageWithDetail(int error, std::string detail)
{
    std::cout << "[Error] " << GetErrorMessage(error) << " : " << detail << std::endl;
}
