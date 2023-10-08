#include "Vector.h"

Vector::Vector(const size_t& size)
{
	this->size = size;
	values = new double[size] {0};
	delete_on_release = true;
}

Vector::Vector(double* values, const size_t& size, bool delete_on_release)
{
	this->delete_on_release = delete_on_release;
	this->size = size;
	this->values = values;
}

Vector::~Vector()
{
	if (delete_on_release)
	{
		delete[] values;
	}
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

size_t Vector::get_size() const
{
	return size;
}

double* Vector::get_values() const
{
	return values;
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
