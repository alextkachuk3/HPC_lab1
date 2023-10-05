#pragma once
#include <iostream>
#include <sstream>

class Matrix
{
public:
	Matrix(int& size);
	~Matrix();

	std::string toString() const;

	friend std::ostream& operator<< (std::ostream& out, const Matrix& matrix);

private:
	void DummyDataInitialization();

	int size;
	double** values;
};

