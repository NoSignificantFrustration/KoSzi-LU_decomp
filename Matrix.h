#pragma once
#include <stdexcept>
#include <string>
#include <iostream>
#include <iomanip> 



template<typename T>
class Matrix
{
public:
	
	int id;

	Matrix();
	Matrix(const Matrix& other);
	Matrix(unsigned n, unsigned m);
	
	~Matrix();

	T& At(unsigned n, unsigned m);
	const T& peek(unsigned n, unsigned m) const;
	Matrix operator *(const Matrix& m) const;
	Matrix operator <<(const Matrix& m) const;
	//Matrix& operator=(const Matrix& a);
	Matrix identity() const;

	Matrix& operator=(const Matrix& other);
	//Matrix& operator=(Matrix&&) { std::cout << "move assign" << name << "\n"; return *this; }

	unsigned height() const;
	unsigned width() const;

	void Print() const;

	std::string name;

	//friend std::ostream& operator<<(std::ostream& os, Matrix<T> const& m);

	//operator std::string() const;

	unsigned get_index(unsigned i, unsigned j) const;

private:
	unsigned size;
	unsigned n;
	unsigned m;
	T* arr;
	
};

#include "Matrix.cpp"
