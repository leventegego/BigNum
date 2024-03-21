#ifndef BIGEXC
#define BIGEXC

#include <stdexcept>
#include <string>

class invalid_operation : public std::logic_error
{
public:
    invalid_operation(const std::string &msg);
};

class invalid_expression : public std::logic_error
{
public:
    invalid_expression(const std::string &msg);
};



#endif


