#include "Matrix.h"

Matrix::Matrix(int& size)
{
	this->size = size;
	values = new double*[size];
	for (int i = 0; i < size; i++)
	{
		values[i] = new double[size];
	}

	DummyDataInitialization();
}

Matrix::~Matrix()
{
	delete[] values;
}

std::string Matrix::toString() const
{
	std::stringstream string;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			string << values[i][j] << " ";
		}
		string << std::endl;
	}
	return string.str();
}

void Matrix::DummyDataInitialization()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			values[i][j] = i;
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
{
	out << matrix.toString();

	return out;
}
