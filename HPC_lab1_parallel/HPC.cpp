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
	distibute_vector(vector);

	distribute_matrix(matrix.get_values(), matrix.get_width());

	return Vector(1);
}

void HPC::matrix_vector_multiplication()
{
	Vector vector = distibute_vector();

	distribute_matrix(nullptr, vector.get_size());
}

int HPC::get_process_rank()
{
	return process_rank;
}

double* HPC::distribute_matrix(const double* matrix, const int& size)
{
	int* send_ind = new int[process_num] {};
	int* send_num = new int[process_num] {};

	int rest_rows = size;
	for (int i = 0; i < process_rank; i++)
		rest_rows = rest_rows - rest_rows / (process_num - i);
	int row_num = rest_rows / (process_num - process_rank);
	double* proc_rows = new double[row_num * size] {};

	rest_rows = size;
	row_num = (size / process_num);
	send_num[0] = row_num * size;
	for (int i = 1; i < process_num; i++) {
		rest_rows -= row_num;
		row_num = rest_rows / (process_num - i);
		send_num[i] = row_num * size;
		send_ind[i] = send_ind[i - 1] + send_num[i - 1];
	}

	MPI_Scatterv(matrix, send_num, send_ind, MPI_DOUBLE, proc_rows,
		send_num[process_rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

	this->log("send_num " + std::to_string(send_num[process_rank]));
	for (int i = 0; i < send_num[process_rank]; i++)
	{
		this->log(std::to_string(i) + " proc_rows " + std::to_string(proc_rows[i]));
	}

	delete[] send_ind;
	delete[] send_num;
	delete[] proc_rows;

	return nullptr;
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

void HPC::log(std::string message)
{
	std::cout << "Process " << process_rank << ": " << message << std::endl;
}
