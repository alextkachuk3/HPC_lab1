#include <iostream>
#include <iomanip>
#include <chrono>

#include "Matrix.h"

bool print_values = false;
bool evaluation_test = false;

void test_matrix_vector_multiplication(const size_t& size)
{
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

int main(int argc, char* argv[])
{
	for (size_t i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-p") == 0)
		{
			print_values = true;
		}
		else if (strcmp(argv[i], "-t") == 0)
		{
			evaluation_test = true;
		}
	}

	if (evaluation_test)
	{
		size_t evaluation_sizes[] = { 10, 100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };

		for (size_t i = 0; i < sizeof(evaluation_sizes) / sizeof(size_t); i++)
		{
			Matrix matrix(evaluation_sizes[i]);
			Vector vector(evaluation_sizes[i]);
			matrix.random_data_initialization();
			vector.random_data_initialization();

			std::cout << "Matrix size " << evaluation_sizes[i] << "x" 
				<< evaluation_sizes[i] << ":" << std::endl;

			test_matrix_vector_multiplication(evaluation_sizes[i]);
		}
		return 0;
	}

	size_t size;

	std::cout << "Enter size of matrix and vector:";

	std::cin >> size;

	test_matrix_vector_multiplication(size);

	return 0;

}
