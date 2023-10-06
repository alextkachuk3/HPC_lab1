#include "Vector.h"

Vector::Vector(const size_t& size)
{
	this->size = size;
	values = new double[size];
}

Vector::~Vector()
{
	delete[] values;
}

std::string Vector::to_string() const
{
	std::stringstream string;
	for (size_t i = 0; i < size; i++)
	{
		string << values[i] << std::endl;
	}
	return string.str();
}

void Vector::dummy_data_initialization()
{
	for (size_t i = 0; i < size; i++)
	{
		values[i] = 1;
	}
}

void Vector::random_data_initialization()
{
	srand(clock());
	for (size_t i = 0; i < size; i++)
	{
		values[i] = rand() / 1000.0;
	}
}

double* Vector::get_values() const
{
	return values;
}

double operator*(const double& matrix, const Vector& vector)
{
	double result = 0.0;

	for (size_t i = 0; i < vector.size; i++)
	{
		result += matrix * vector.values[i];
	}

	return result;
}

std::ostream& operator<<(std::ostream& out, const Vector& vector)
{
	out << vector.to_string();

	return out;
}

double* Vector::operator[](size_t index) const
{
	return &values[index];
}
