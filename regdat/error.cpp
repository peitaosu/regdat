#include "error.h"

std::string GetErrorMessage(int error)
{
    return Errors.find(error)->second;
}

void PrintErrorMessage(int error)
{
    std::cout << "[Error]: " << GetErrorMessage(error) << std::endl;
}
