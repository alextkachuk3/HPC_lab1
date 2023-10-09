#pragma once
#include <mpi.h>

#include "../HPC_lab1_serial/Vector.h"
#include "../HPC_lab1_serial/Matrix.h"

class HPC
{
public:
	HPC(int argc, char* argv[]);
	~HPC();
	Vector matrix_vector_multiplication(const Matrix& matrix, const Vector& vector);
	void matrix_vector_multiplication();

	int get_process_rank();

private:
	Matrix distribute_matrix(const double* matrix, const int& size);
	Matrix distribute_matrix(const int& size);
	void distibute_vector(const Vector& vector);
	Vector distibute_vector();
	void process_matrix_distribution(int* send_ind, int* send_num, const int& size);

	void log(std::string message);

	int process_num;
	int process_rank;
};
