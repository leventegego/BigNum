#include "expression.h"


bignum expression::evaluate() const
{
    std::stack<bignum> stack;
    for(const std::string &seg : segments)
    {
        if(bignum::valid(seg))
        {
            stack.push(bignum(seg));
        }
        else if(operation::valid(seg))
        {
            if(stack.size() < 2)
                throw invalid_expression("ran out of constants!");

            bignum a = stack.top(); stack.pop();
            bignum b = stack.top(); stack.pop();
            stack.push(operation(seg).evaluate(b, a));
        }
        else
        {
            throw invalid_expression("invalid token!");
        }
    }

    if(stack.empty())
        throw invalid_expression("empty expression!");

    return stack.top();
}

std::istream &operator>>(std::istream &is, expression &x)
{
    std::string line;
    std::getline(is, line);
    std::stringstream ss(line);
    x.segments = std::vector<std::string>(
            std::istream_iterator<std::string>(ss),
            std::istream_iterator<std::string>());
    return is;
}

operation::operation(const std::string &str) : op(str[0]) { }

bignum operation::evaluate(const bignum &a, const bignum &b) const
{
    switch(op)
    {
    case '+': return a + b; break;
    case '-': return a - b; break;
    case '*': return a * b; break;
    case '/': return a / b; break;
    default: return 0;
    }
}

bool operation::valid(const std::string &str)
    { return str.size() == 1 && std::string("+-*/").find(str[0]) != std::string::npos; }
