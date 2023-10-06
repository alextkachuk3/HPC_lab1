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
	size_t size = matrix.get_size();
	MPI_Bcast(&size, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
	return Vector(0);
}

void HPC::matrix_vector_multiplication_subprocess()
{
	size_t size = 0;
	MPI_Bcast(&size, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
	log(std::to_string(size));	
}

int HPC::get_process_rank()
{
	return process_rank;
}

void HPC::log(std::string message)
{
	std::cout << "Process " << process_rank << ": " << message << std::endl;
}
