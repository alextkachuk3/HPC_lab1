#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>

#include "Vector.h"

class Matrix
{
public:
	Matrix(const size_t& size);
	~Matrix();

	void dummy_data_initialization();

	std::string to_string() const;

	size_t get_size() const;
	void set_output_wide(size_t& outputWide);

	friend Vector operator*(const Matrix& m, const Vector& v);
	friend std::ostream& operator<< (std::ostream& out, const Matrix& matrix);

private:
	size_t size;
	double** values;

	size_t outputWide;
	const static size_t defaultOutputWide = 2;
};
