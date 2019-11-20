#include "error.h"

namespace regdat {
    std::string get_error_message(int error)
    {
        return Errors.find(error)->second;
    }

    void print_error(int error)
    {
        std::cout << "[Error] " << get_error_message(error) << std::endl;
    }

    void print_error_detail(int error, std::string detail)
    {
        std::cout << "[Error] " << get_error_message(error) << " : " << detail << std::endl;
    }
}
