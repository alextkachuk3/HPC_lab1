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

		hpc.matrix_vector_multiplication_init(matrix, vector);
	}
	hpc.matrix_vector_multiplication();
}
