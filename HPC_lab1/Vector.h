#pragma once
#include <iostream>
#include <sstream>

class Vector
{
public:
	Vector(const size_t& size);
	~Vector();

	void dummy_vector_generation();

	std::string to_string() const;

	friend double operator*(double*& m, const Vector& v);

	double* operator[](size_t index) const;

	friend std::ostream& operator<< (std::ostream& out, const Vector& vector);

private:
	size_t size;
	double* values;
};

