#include "bigexc.h"

invalid_operation::invalid_operation(const std::string &msg)
    : std::logic_error(msg) { }

invalid_expression::invalid_expression(const std::string &msg)
    : std::logic_error(msg) { }
