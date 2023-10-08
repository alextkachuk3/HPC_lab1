#include <iostream>
#include <iomanip>

#include "Matrix.h"

int main()
{
	time_t start, finish;
	size_t size;
	double duration;

	std::cout << "Enter size of matrix and vector:";

	std::cin >> size;

	start = clock();

	Matrix matrix(size);
	Vector vector(size);
	matrix.dummy_data_initialization();
	vector.dummy_data_initialization();
	//matrix.random_data_initialization();
	//vector.random_data_initialization();

	Vector result = matrix * vector;

	size_t outputWide = 10;
	size_t maxOutputMatrixSizeLimit = 15;

	matrix.set_output_wide(outputWide);

	if (size <= maxOutputMatrixSizeLimit)
	{
		std::cout << "Matrix" << std::endl << matrix;

		std::cout << "Vector" << std::endl << vector;

		std::cout << "Result vector:" << std::endl << result;
	}

	finish = clock();

	duration = (finish - start) / double(CLOCKS_PER_SEC);

	std::cout << std::endl << "Time of execution: " << duration << std::endl;

}
