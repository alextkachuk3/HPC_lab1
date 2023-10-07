#pragma once
#include <iostream>
#include <sstream>

class Vector
{
public:
	Vector(const size_t& size);
	~Vector();

	void dummy_data_initialization();
	void random_data_initialization();
	double* get_values() const;

	std::string to_string() const;

	double* operator[](size_t index) const;

	friend std::ostream& operator<< (std::ostream& out, const Vector& vector);

private:
	size_t size;
	double* values;
};
