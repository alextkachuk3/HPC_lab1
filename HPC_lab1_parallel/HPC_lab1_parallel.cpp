#include <iostream>
#include "HPC.h"

size_t evaluation_sizes[] = { 10, 100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };

bool print_values = false;
bool evaluation_test = false;

void test_matrix_vector_multiplication(const size_t& size, HPC& hpc)
{
	Matrix matrix(size);
	Vector vector(size);

	matrix.random_data_initialization();
	vector.random_data_initialization();

	double start, finish, duration;

	start = MPI_Wtime();

	Vector result = hpc.matrix_vector_multiplication(matrix, vector);

	finish = MPI_Wtime();
	duration = finish - start;

	if (print_values)
	{
		size_t outputWide = 10;
		matrix.set_output_wide(outputWide);

		std::cout << "Matrix" << std::endl << matrix;
		std::cout << "Vector" << std::endl << vector;		
		std::cout << "Result:" << std::endl << result;
	}

	std::cout << "Time of execution = " << std::fixed << std::setprecision(12) << duration << std::endl;

	if (result == matrix * vector)
	{
		std::cout << "The results of serial and parallel algorithms are identical!" << std::endl;
	}
	else
	{
		std::cout << "The results of serial and parallel algorithms are NOT identical!" << std::endl;
	}
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

	HPC hpc(argc, argv);

	if (hpc.get_process_rank() == 0)
	{
		if (evaluation_test)
		{
			for (size_t i = 0; i < sizeof(evaluation_sizes) / sizeof(size_t); i++)
			{
				Matrix matrix(evaluation_sizes[i]);
				Vector vector(evaluation_sizes[i]);
				matrix.random_data_initialization();
				vector.random_data_initialization();

				std::cout << std::endl << "Matrix size " << evaluation_sizes[i] << "x"
					<< evaluation_sizes[i] << ":" << std::endl;

				test_matrix_vector_multiplication(evaluation_sizes[i], hpc);
			}
			return 0;
		}

		size_t size;
		std::cout << "Enter size of matrix and vector:";
		std::cin >> size;
		test_matrix_vector_multiplication(size, hpc);

	}
	else
	{
		if (evaluation_test)
		{
			for (size_t i = 0; i < sizeof(evaluation_sizes) / sizeof(size_t); i++)
			{
				hpc.matrix_vector_multiplication();
			}
		}
		else
		{
			hpc.matrix_vector_multiplication();
		}
	}

}
