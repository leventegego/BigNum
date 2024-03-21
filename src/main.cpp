#include <iostream>
#include "bignum.h"
#include "expression.h"

int main()
{
    expression e;
    while(std::cin >> e)
    {
        try
        {
            std::cout << e.evaluate() << std::endl;
        }
        catch(std::exception &exc)
        {
            std::cout << exc.what() << std::endl;
        }
    }
    return 0;
}

