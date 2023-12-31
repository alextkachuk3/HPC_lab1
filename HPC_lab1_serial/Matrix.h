#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>

#include "Vector.h"

class Matrix
{
public:
	Matrix(const size_t& size);
	Matrix(double* values, const size_t& width, const size_t& height, const bool& delete_on_release = false);
	~Matrix();

	void dummy_data_initialization();
	void random_data_initialization();

	std::string to_string() const;
	size_t get_width() const;
	size_t get_height() const;
	size_t get_submatrix_index() const;
	double* get_values() const;

	void set_submutrix_index(const size_t& submatrix_index);
	void set_output_wide(const size_t& outputWide);
	
	bool operator==(const Matrix& other);
	friend Vector operator*(const Matrix& m, const Vector& v);

	friend std::ostream& operator<< (std::ostream& out, const Matrix& matrix);

private:
	size_t height;
	size_t width;
	size_t submatrix_index;
	double* values;

	bool delete_on_release;

	size_t outputWide;
	const static size_t defaultOutputWide = 7;
};
