#include <iostream>
#include <iomanip>

#include "Matrix.h"

int main()
{
    std::cout << "Enter size of matrix:";
    size_t size;
    std::cin >> size;

    Matrix matrix(size);
    Vector vector(size);
    //matrix.dummy_data_initialization();
    //vector.dummy_data_initialization();
    matrix.random_data_initialization();
    vector.random_data_initialization();

    Vector result = matrix * vector;

    size_t outputWide = 10;

    matrix.set_output_wide(outputWide);
    
    std::cout << "Matrix" << std::endl << matrix;

    std::cout << "Vector" << std::endl << vector;

    std::cout << "Result vector:" << std::endl << result;
}
