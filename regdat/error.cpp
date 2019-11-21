#include "error.h"

namespace regdat {
    std::string get_error_message(int error)
    {
        return Errors.find(error)->second;
    }

    void print_error(int error)
    {
        std::cout << "[ERROR] " << get_error_message(error) << std::endl;
    }

    void print_error(int level, int error)
    {
        std::string level_string = "[ERROR]";
        if (level == 1) {
            level_string = "[WARNN]";
        }
        if (level == 2) {
            level_string = "[INFOR]";
        }
        std::cout << level_string << " " << get_error_message(error) << std::endl;
    }

    void print_error(int level, int error, std::string detail)
    {
        std::string level_string = "[ERROR]";
        if (level == 1) {
            level_string = "[WARNN]";
        }
        if (level == 2) {
            level_string = "[INFOR]";
        }
        std::cout << level_string << " " << get_error_message(error) << " : " << detail << std::endl;
    }
}
