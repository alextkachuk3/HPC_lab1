#pragma once
#include <mpi.h>

#include "../HPC_lab1_serial/Vector.h"
#include "../HPC_lab1_serial/Matrix.h"

class HPC
{
public:
	HPC(int argc, char* argv[]);
	~HPC();
	Vector matrix_vector_multiplication_init(const Matrix& matrix, const Vector& vector);
	void matrix_vector_multiplication();

	int get_process_rank();

	size_t size = 0;

private:
	void log(std::string message);

	int process_num;
	int process_rank;
};

