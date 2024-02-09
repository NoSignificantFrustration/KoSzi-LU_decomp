#pragma once
#include "Fraction.h"
#include "Matrix.h"
#include <vector>

template<typename T>
class LU_Decomp
{
public:
	LU_Decomp( Matrix<T> & A);
	//~LU_Decomp();

	std::vector<T> SolveLinear(std::vector<T>const& b) const;
	const Matrix<T>& a() const;
	const Matrix<T>& l() const;
	const Matrix<T>& u() const;

private:
	Matrix<T> A;
	Matrix<T> L;
	Matrix<T> U;
	void Decomp();
};

#include "LU_Decomp.cpp"