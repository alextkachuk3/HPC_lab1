#pragma once
#include <mpi.h>

#include "../HPC_lab1_serial/Vector.h"
#include "../HPC_lab1_serial/Matrix.h"

class HPC
{
public:
	HPC(int argc, char* argv[]);
	~HPC();
	Vector MatrixVectorMultiplication(const Matrix& matrix, const Vector& vector);

private:
	void Log(std::string message);

	int process_num;
	int process_rank;
};

