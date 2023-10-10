#include "HPC.h"

HPC::HPC(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
}

HPC::~HPC()
{
	MPI_Finalize();
}

Vector HPC::matrix_vector_multiplication(const Matrix& matrix, const Vector& vector)
{
	int* send_ind = new int[process_num];
	int* send_num = new int[process_num];

	int size = (int)vector.get_size();

	process_matrix_distribution(send_ind, send_num, size);

	distibute_vector(vector);
	Matrix distributed_matrix = distribute_matrix(matrix.get_values(), size, send_ind, send_num);

	Vector res = distributed_matrix * vector;

	double* final_result = new double[vector.get_size()];

	for (int i = 0; i < process_num; i++)
	{
		send_ind[i] /= size;
		send_num[i] /= size;
	}

	MPI_Allgatherv(res.get_values(), (int)res.get_size(), MPI_DOUBLE, final_result,
		send_num, send_ind, MPI_DOUBLE, MPI_COMM_WORLD);

	delete[] send_ind;
	delete[] send_num;

	MPI_Barrier(MPI_COMM_WORLD);

	return Vector(final_result, vector.get_size(), true);
}

void HPC::matrix_vector_multiplication()
{
	int* send_ind = new int[process_num];
	int* send_num = new int[process_num];

	Vector vector = distibute_vector();

	int size = (int)vector.get_size();

	process_matrix_distribution(send_ind, send_num, size);

	Matrix distributed_matrix = distribute_matrix(size, send_ind, send_num);

	Vector res = distributed_matrix * vector;

	double* final_result = new double[vector.get_size()];

	for (int i = 0; i < process_num; i++)
	{
		send_ind[i] /= size;
		send_num[i] /= size;
	}

	MPI_Allgatherv(res.get_values(), (int)res.get_size(), MPI_DOUBLE, final_result,
		send_num, send_ind, MPI_DOUBLE, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);

	delete[] send_ind;
	delete[] send_num;
}

int HPC::get_process_rank()
{
	return process_rank;
}

Matrix HPC::distribute_matrix(double* matrix, const int& size, int*& send_ind, int*& send_num)
{
	double* proc_rows = new double[send_num[process_rank]];

	MPI_Scatterv(matrix, send_num, send_ind, MPI_DOUBLE, proc_rows,
		send_num[process_rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

	Matrix result = Matrix(matrix, size, size / process_num, false);
	result.set_submutrix_index(send_ind[process_rank]);

	return result;
}

Matrix HPC::distribute_matrix(const int& size, int*& send_ind, int*& send_num)
{
	double* proc_rows = new double[send_num[process_rank]];

	MPI_Scatterv(nullptr, nullptr, nullptr, MPI_DOUBLE, proc_rows, send_num[process_rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

	Matrix result = Matrix(proc_rows, size, send_num[process_rank] / size, true);
	result.set_submutrix_index(send_ind[process_rank]);

	return result;
}

void HPC::distibute_vector(const Vector& vector)
{
	int size = (int)vector.get_size();
	MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Bcast(vector.get_values(), size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

Vector HPC::distibute_vector()
{
	int size = 0;
	MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

	double* values = new double[size] {};
	MPI_Bcast(values, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	return Vector(values, size, true);
}

void HPC::process_matrix_distribution(int* send_ind, int* send_num, const int& size)
{
	int rest_rows = size;
	int row_num = size / process_num;
	int cur_row = 0;

	if (process_num >= 2)
	{
		send_num[0] = row_num * size;
		send_ind[0] = 0;
		for (int i = 1; i < process_num; i++) {
			rest_rows -= row_num;
			row_num = rest_rows / (process_num - i);
			send_num[i] = row_num * size;
			send_ind[i] = send_ind[i - 1] + send_num[i - 1];
		}
	}
	else
	{
		send_num[0] = 0;
		send_ind[0] = 0;
	}
}

void HPC::log(std::string message)
{
	std::cout << "Process " << process_rank << ": " << message << std::endl;
}
