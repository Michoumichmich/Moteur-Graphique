#include <iostream>
#include "Vector.h"

double len;

int main()
{
    Vector a(1, 1, 1);
    Vector b(2, 0, -2);

    len = b.length();

    std::cout << "a:\t" << a << std::endl
              << "b:\t" << b << std::endl
              << "a.x:\t" << a.x << std::endl
              << "add:\t" << a+b << std::endl
              << "sub:\t" << a-b << std::endl
              << "dot:\t" << a.dot(b) << std::endl
              << "smult:\t" << len << std::endl;
    return 0;
}