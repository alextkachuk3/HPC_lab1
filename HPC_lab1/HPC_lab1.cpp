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
    vector.dummy_vector_generation();

    Vector result = matrix * vector;

    size_t outputWide = std::to_string(size).length() + 1;

    matrix.set_output_wide(outputWide);
    
    std::cout << "Matrix" << std::endl << matrix;

    std::cout << "Vector" << std::endl << vector;

    std::cout << "Result vector:" << std::endl << result;
}