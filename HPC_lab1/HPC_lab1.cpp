#include <iostream>

#include "Matrix.h"

int main()
{
    std::cout << "Hello World!\n";
    int size;
    std::cin >> size;
    Matrix matrix(size);
    std::cout << matrix;
}