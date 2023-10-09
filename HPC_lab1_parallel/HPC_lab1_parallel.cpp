#include <iostream>
#include "HPC.h"

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

	HPC hpc(argc, argv);

	if (hpc.get_process_rank() == 0)
	{
		size_t size;
		std::cout << "Enter size of matrix and vector:";
		std::cin >> size;

		Matrix matrix(size);
		Vector vector(size);

		matrix.random_data_initialization();
		vector.random_data_initialization();
		matrix.dummy_data_initialization();
		vector.dummy_data_initialization();

		double start, finish, duration;

		start = MPI_Wtime();

		Vector result = hpc.matrix_vector_multiplication(matrix, vector);

		finish = MPI_Wtime();
		duration = finish - start;

		if (print_values)
		{
			size_t outputWide = 7;
			matrix.set_output_wide(outputWide);

			std::cout << "Vector" << std::endl << vector;
			std::cout << "Matrix" << std::endl << matrix;
			std::cout << "Result:" << std::endl << result;
		}

		std::cout << "Time of execution = " << std::setprecision(15) << duration << std::endl;

		if (result == matrix * vector)
		{
			std::cout << "The results of serial and parallel algorithms are identical!" << std::endl;
		}
		else
		{
			std::cout << "The results of serial and parallel algorithms are NOT identical!" << std::endl;
		}
	}
	else
	{
		hpc.matrix_vector_multiplication();
	}

}
