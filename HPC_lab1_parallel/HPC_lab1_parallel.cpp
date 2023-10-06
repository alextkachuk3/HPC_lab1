#include <iostream>
#include "HPC.h"

int main(int argc, char* argv[])
{
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

		size_t outputWide = 10;
		size_t maxOutputMatrixSizeLimit = 15;

		matrix.set_output_wide(outputWide);

		std::cout << "Matrix" << std::endl << matrix;

		hpc.matrix_vector_multiplication(matrix, vector);
	}
	else
	{
		hpc.matrix_vector_multiplication();
	}

}
