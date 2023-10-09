#include <iostream>
#include <iomanip>
#include <chrono>

#include "Matrix.h"

int main(int argc, char* argv[])
{
	bool print_values = false;

	for (size_t i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-p") == 0)
		{
			print_values = true;
		}
	}

	size_t size;

	std::cout << "Enter size of matrix and vector:";

	std::cin >> size;

	Matrix matrix(size);
	Vector vector(size);
	matrix.random_data_initialization();
	vector.random_data_initialization();

	auto start = std::chrono::high_resolution_clock::now();

	Vector result = matrix * vector;

	auto finish = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() * 1.0e-9;

	if (print_values)
	{
		size_t outputWide = 10;
		matrix.set_output_wide(outputWide);

		std::cout << "Matrix" << std::endl << matrix;
		std::cout << "Vector" << std::endl << vector;
		std::cout << "Result vector:" << std::endl << result;
	}

	std::cout << std::endl << "Time of execution: " << std::fixed << std::setprecision(40) << duration << std::endl;

}
