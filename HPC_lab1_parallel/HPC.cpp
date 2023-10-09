#include "HPC.h"

HPC::HPC(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

	this->log("Process started!");
}

HPC::~HPC()
{
	this->log("Process ended!");
	MPI_Finalize();
}

Vector HPC::matrix_vector_multiplication(const Matrix& matrix, const Vector& vector)
{
	int* send_ind = new int[process_num];
	int* send_num = new int[process_num];

	process_matrix_distribution(send_ind, send_num, vector.get_size());

	distibute_vector(vector);
	Matrix distributed_matrix = distribute_matrix(matrix.get_values(), matrix.get_height());
	//std::cout << distributed_matrix.to_string();
	Vector res = distributed_matrix * vector;
	//std::cout << res;

	double* final_result = new double[vector.get_size()];

	for (int i = 0; i < process_num; i++)
	{
		send_ind[i] /= vector.get_size();
		send_num[i] /= vector.get_size();
	}

	MPI_Allgatherv(res.get_values(), res.get_size(), MPI_DOUBLE, final_result,
		send_num, send_ind, MPI_DOUBLE, MPI_COMM_WORLD);

	delete[] send_ind;
	delete[] send_num;

	return Vector(final_result, vector.get_size(), true);
}

void HPC::matrix_vector_multiplication()
{
	Vector vector = distibute_vector();
	Matrix distributed_matrix = distribute_matrix(vector.get_size());
	//std::cout << distributed_matrix.to_string();
	//log(std::to_string(distributed_matrix.get_submatrix_index()));
	Vector res = distributed_matrix * vector;
	//std::cout << res;

	int* send_ind = new int[process_num];
	int* send_num = new int[process_num];

	process_matrix_distribution(send_ind, send_num, vector.get_size());

	double* final_result = new double[vector.get_size()];

	for (int i = 0; i < process_num; i++)
	{
		send_ind[i] /= vector.get_size();
		send_num[i] /= vector.get_size();
	}

	MPI_Allgatherv(res.get_values(), res.get_size(), MPI_DOUBLE, final_result,
		send_num, send_ind, MPI_DOUBLE, MPI_COMM_WORLD);

	delete[] send_ind;
	delete[] send_num;
}

int HPC::get_process_rank()
{
	return process_rank;
}

Matrix HPC::distribute_matrix(const double* matrix, const int& size)
{
	int* send_ind = new int[process_num];
	int* send_num = new int[process_num];

	process_matrix_distribution(send_ind, send_num, size);

	double* proc_rows = new double[send_num[process_rank]];

	MPI_Scatterv(matrix, send_num, send_ind, MPI_DOUBLE, proc_rows,
		send_num[process_rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

	Matrix result = Matrix(proc_rows, size, send_num[process_rank] / size, true);
	result.set_submutrix_index(send_ind[process_rank]);

	delete[] send_ind;
	delete[] send_num;

	return result;
}

Matrix HPC::distribute_matrix(const int& size)
{
	return distribute_matrix(nullptr, size);
}

void HPC::distibute_vector(const Vector& vector)
{
	size_t size = vector.get_size();
	MPI_Bcast(&size, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);

	MPI_Bcast(vector.get_values(), size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

Vector HPC::distibute_vector()
{
	size_t size = 0;
	MPI_Bcast(&size, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);

	double* values = new double[size] {};
	MPI_Bcast(values, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	return Vector(values, size, true);
}

void HPC::process_matrix_distribution(int* send_ind, int* send_num, const int& size)
{
	int rest_rows = size;
	int row_num = size / process_num;
	int cur_row = 0;

	send_num[0] = row_num * size;
	send_ind[0] = 0;
	for (int i = 1; i < process_num; i++) {
		rest_rows -= row_num;
		row_num = rest_rows / (process_num - i);
		send_num[i] = row_num * size;
		send_ind[i] = send_ind[i - 1] + send_num[i - 1];
	}
}

void HPC::log(std::string message)
{
	std::cout << "Process " << process_rank << ": " << message << std::endl;
}
