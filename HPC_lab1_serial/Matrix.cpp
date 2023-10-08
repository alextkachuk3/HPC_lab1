#include "Matrix.h"

Matrix::Matrix(const size_t& size)
{
	outputWide = defaultOutputWide;

	this->width = size;
	this->height = size;

	values = new double[size * size];
	this->delete_on_release = true;
}

Matrix::Matrix(double* values, const size_t& width, const size_t& height, const bool& delete_on_release)
{
	outputWide = defaultOutputWide;

	this->values = values;
	this->width = width;
	this->height = height;
	this->delete_on_release = delete_on_release;
}

Matrix::~Matrix()
{
	if (delete_on_release)
	{
		delete[] values;
	}
}

std::string Matrix::to_string() const
{
	std::stringstream string;
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			string << std::setw(outputWide) << values[i * height + j];
		}
		string << std::setw(0) << std::endl;
	}
	return string.str();
}

size_t Matrix::get_width() const
{
	return width;
}

size_t Matrix::get_height() const
{
	return height;
}

double* Matrix::get_values() const
{
	return values;
}

void Matrix::set_output_wide(size_t& outputWide)
{
	this->outputWide = outputWide;
}

void Matrix::dummy_data_initialization()
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			values[i * height + j] = (double)i;
		}
	}
}

void Matrix::random_data_initialization()
{
	srand(clock());
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			values[i * height + j] = rand() / 1000.0;
		}
	}
}

Vector operator*(const Matrix& m, const Vector& v)
{
	Vector result(m.height);

	for (size_t i = 0; i < m.height; i++)
	{
		for (size_t j = 0; j < m.width; j++)
		{
			*result[i] += m.values[i * m.height + j] * v.get_values()[j];
		}
	}

	return result;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
{
	out << matrix.to_string();

	return out;
}
