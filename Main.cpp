#include <iostream>
#include <iomanip> 
#include <string>
#include <vector>
#include <boost/chrono/chrono.hpp>
#include "Fraction.h"
#include "Matrix.h"
#include "LU_Decomp.h"



using LongFloat = boost::multiprecision::cpp_bin_float_quad;

//Ezt ird at, ha tipust akarsz valtani. (LongFloat vagy Fraction)
//**********************
using T = LongFloat;
//**********************

int main() {
	std::string str;

	unsigned n;

	std::cout << "Input the size of matrix A\n";

	std::cin >> n;

	

	Matrix<T> m = Matrix<T>(n, n);

	std::cout << "Input matrix A\n";

	for (unsigned i = 0; i < m.height(); i++)
	{
		for (unsigned j = 0; j < m.width(); j++)
		{
			T num;
			std::cin >> num;
			m.At(i, j) = num;
		}

	} 


	boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();

	LU_Decomp<T> lu(m);

	boost::chrono::duration<double> sec = boost::chrono::system_clock::now() - start;
	std::cout << "\nLU decomposition complete in " << sec.count() << " seconds\n\n";

	std::vector<T> b(m.width());

	std::cout << "Print L and U matrices? (y/n)\n";

	while (true)
	{
		char c;
		std::cin >> c;

		if (c == 'y')
		{
			std::cout << "L:\n";
			lu.l().Print();
			std::cout << "U:\n";
			lu.u().Print();
			break;
		}
		else if(c == 'n')
		{
			break;
		}
	}



	std::cout << "Solve a linear equation with decomposed matrix? (y/n)\n";

	while (true)
	{
		char c;
		std::cin >> c;

		if (c == 'y')
		{
			std::cout << "Input vector b\n";

			for (unsigned j = 0; j < m.width(); j++)
			{
				T num;
				std::cin >> num;
				b[j] = num;
			}
			start = boost::chrono::system_clock::now();

			b = lu.SolveLinear(b);

			sec = boost::chrono::system_clock::now() - start;

			std::cout << "\nLinear equation solved in " << sec.count() << " seconds\n\n";

			std::cout << "\n";

			for (unsigned i = 0; i < b.size(); i++)
			{
				std::cout << "x" << i + 1 << "= " << b[i] << "\n";
			}
			std::cout << "\n";

			std::cout << "Solve a linear equation with decomposed matrix? (y/n)\n";
			
		}
		else if (c == 'n')
		{
			break;
		}
	}

	return 0;
}

