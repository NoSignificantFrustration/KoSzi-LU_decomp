#include <stdexcept>
#include "LU_Decomp.h"

#ifndef LU_DECOMP_CPP
#define LU_DECOMP_CPP

template<typename T>
LU_Decomp<T>::LU_Decomp( Matrix<T> & A) : A(A), L(A.identity()), U(A) {
	if (A.height() != A.width())
	{
		throw std::invalid_argument("Matrix A must be square");
	}
	Decomp();

}


template<typename T>
void LU_Decomp<T>::Decomp() {

	for (unsigned i = 0; i < A.width() - 1; i++)
	{
		bool isBottomTri = true;
		Matrix<T> Ln = A.identity();
		for (unsigned j = i + 1; j < A.height(); j++)
		{
			
			if (U.At(i, i) == 0)
			{
				isBottomTri = false;
				Ln.At(i - 1, i) = 1;
				for (unsigned k = i; k < A.width(); k++)
				{
					U.At(i, k) += U.At(i + 1, k);
				}
			}
			T eliminator = U.At(j, i) / U.At(i, i);
			
			Ln.At(j, i) = eliminator;

			for (unsigned k = 0; k < A.width(); k++)
			{
				
				U.At(j, k) -= U.At(i, k) * eliminator;
			}
			/*std::cout << "-----------------------------------\n";
			U.Print();
			std::cout << "-----------------------------------\n";*/
		}

		if (isBottomTri)
		{
			L = L << Ln;
		}
		else
		{
			L = L * Ln;
		}
		
		
	}


	

}

template<typename T>
const Matrix<T>& LU_Decomp<T>::a() const {
	return A;
}
template<typename T>
const Matrix<T>& LU_Decomp<T>::l() const {
	return L;
}
template<typename T>
const Matrix<T>& LU_Decomp<T>::u() const {
	return U;
}

template<typename T>
std::vector<T> LU_Decomp<T>::SolveLinear(std::vector<T>const& _b) const {
	if (_b.size() != A.width())
	{
		throw std::invalid_argument("Vector size mismatch");
	}

	std::vector<T> b = std::vector<T>(_b);

	for (unsigned i = 1; i < A.width(); i++)
	{
		for (unsigned j = 0; j < i; j++)
		{
			
			b[i] -= b[j] * L.peek(i, j);
		}
	}

	for (int i = A.width() - 1; i >= 0; i--)
	{
		for (int j = A.width() - 1; j > i; j--)
		{
			//std::cout << (std::string)b[i] << " - " << (std::string)(b[j] * U.peek(i, j));
			b[i] -= b[j] * U.peek(i, j);
			//std::cout << " = " << (std::string)b[i] << "\n";
		}

		/*std::cout << "\n";
		std::cout << (std::string)b[i] << " : " << (std::string)U.peek(i, i);*/
		b[i] /= U.peek(i, i);
		//std::cout << " = " << (std::string)b[i] << "\n";

	}

	/*std::string str;

	for (unsigned i = 0; i < A.width(); i++)
	{
		str = b[i];
		std::cout << str << " ";
	}
	std::cout << "\n";*/

	return b;
}

#endif // !LU_DECOMP_CPP