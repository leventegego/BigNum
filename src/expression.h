#ifndef EXPRESSION
#define EXPRESSION

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include "bignum.h"
#include "bigexc.h"


// a numeric operation
// can be one of '+-*/'
class operation
{
private:

    char op;

public:

    operation(const std::string &str);
    bignum evaluate(const bignum &a, const bignum &b) const;

    static bool valid(const std::string &str);

};

// an expression in reverse polish notation
class expression
{
private:

    std::vector<std::string> segments;

public:

    friend std::istream &operator>>(std::istream &is, expression &x);
    bignum evaluate() const;

};


#endif


