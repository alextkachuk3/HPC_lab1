#include "Matrix.h"

Matrix::Matrix(const size_t& size)
{
	outputWide = defaultOutputWide;

	this->size = size;

	values = new double* [size];
	for (size_t i = 0; i < size; i++)
	{
		values[i] = new double[size];
	}

	dummy_data_initialization();
}

Matrix::~Matrix()
{
	for (size_t i = 0; i < size; i++)
	{
		delete[] values[i];
	}
	delete[] values;
}

std::string Matrix::to_string() const
{
	std::stringstream string;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			string << values[i][j] << std::setw(outputWide);
		}
		string << std::setw(0) << std::endl;
	}
	return string.str();
}

size_t Matrix::get_size() const
{
	return size;
}

void Matrix::set_output_wide(size_t& outputWide)
{
	this->outputWide = outputWide;
}

void Matrix::dummy_data_initialization()
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			values[i][j] = i;
		}
	}
}

Vector operator*(const Matrix& m, const Vector& v)
{
	Vector result(m.size);

	for (size_t i = 0; i < m.size; i++)
	{
		*result[i] = m.values[i] * v;
	}

	return result;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
{
	out << matrix.to_string();

	return out;
}
