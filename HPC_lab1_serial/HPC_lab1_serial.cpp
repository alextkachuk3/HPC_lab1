#include <iostream>
#include <iomanip>

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

	time_t start, finish;
	size_t size;
	double duration;

	std::cout << "Enter size of matrix and vector:";

	std::cin >> size;

	Matrix matrix(size);
	Vector vector(size);
	matrix.random_data_initialization();
	vector.random_data_initialization();

	start = clock();

	Vector result = matrix * vector;

	finish = clock();

	duration = (finish - start) / double(CLOCKS_PER_SEC);

	if (print_values)
	{
		size_t outputWide = 10;
		matrix.set_output_wide(outputWide);

		std::cout << "Matrix" << std::endl << matrix;
		std::cout << "Vector" << std::endl << vector;
		std::cout << "Result vector:" << std::endl << result;
	}

	std::cout << std::endl << "Time of execution: " << std::setprecision(15) << duration << std::endl;

}
