#include "HPC.h"

HPC::HPC(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

	this->Log("Process started!");

	if (process_rank == 0)
	{
		
	}
}

HPC::~HPC()
{
	this->Log("Process ended!");
	MPI_Finalize();
}

Vector HPC::MatrixVectorMultiplication(const Matrix& matrix, const Vector& vector)
{
	return Vector(0);
}

void HPC::Log(std::string message)
{
	std::cout << "Process " << process_rank << ": " << message << std::endl;
}
