#include "Matrix.h"


#ifndef MATRIX_CPP
#define MATRIX_CPP


static int instanceID = 0;

template<typename T>
Matrix<T>::Matrix() : n(n), m(m), size(n* m) {
	id = instanceID++;
	name = "default";
	//std::cout << "Create default (" << id << ")\n";
}

template<typename T>
Matrix<T>::Matrix(unsigned n, unsigned m) : n(n), m(m), size(n * m) {
	if (n == 0 || m == 0)
	{
		throw std::invalid_argument("Matrix dimensions cannot be zero");
	}
	id = instanceID++;
	//std::cout << "Create normal (" << id << ")\n";
	name = "tmp";
	arr = new T[size];
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & other) : n(other.height()), m(other.width()), size(other.height() * other.width()) {
	if (size == 0)
	{
		throw std::invalid_argument("Matrix dimensions cannot be zero");
	}
	id = instanceID++;
	if (name.empty())
	{
		name = "copy";
	}
	//std::cout << "Create copy (" << id << ")\n";

	arr = new T[size];
	for (unsigned i = 0; i < n; i++)
	{
		for (unsigned j = 0; j < m; j++)
		{
			At(i, j) = other.peek(i, j);
		}
	}

	
	
}


template<typename T>
Matrix<T>::~Matrix(){
	//std::cout << "Delete " << name << "  " << id << '\n';
	delete[](arr);
}




template<typename T>
T& Matrix<T>::At(unsigned n, unsigned m) {
	if (n * m >= size)
	{
		throw std::invalid_argument("Index is outside of the bounds of matrix");
	}
	//std::cout << "Access " << arr << "\n";
	return arr[n * this->m + m];
}

template<typename T>
const T& Matrix<T>::peek(unsigned n, unsigned m) const {
	if (n * m >= size)
	{
		throw std::invalid_argument("Index is outside of the bounds of matrix");
	}

	return arr[n * this->m + m];
}

template<typename T>
Matrix<T> Matrix<T>::operator *(const Matrix& other) const {
	if (m != other.height())
	{
		throw std::invalid_argument("Matrix multiplication dimension mismatch");
	}

	Matrix<T> product = Matrix(n, other.width());


	for (unsigned i = 0; i < n; i++)
	{
		for (unsigned j = 0; j < other.width(); j++)
		{
			T sum = 0;
			for (unsigned k = 0; k < m; k++)
			{

				sum += peek(i, k) * other.peek(k, j);
			}

			product.At(i, j) = sum;
		}
	}

	return product;
}


//Lower triangular multiplication
template<typename T>
Matrix<T> Matrix<T>::operator <<(const Matrix& other) const {
	if (n != other.height() || m != other.width())
	{
		throw std::invalid_argument("Matrix multiplication dimension mismatch");
	}
	Matrix<T> product = identity();

	for (unsigned i = 1; i < n; i++)
	{
		for (unsigned j = 0; j < i; j++)
		{
			T sum = 0;
			for (unsigned k = j; k <= i; k++)
			{
				sum += peek(i, k) * other.peek(k, j);
			}
			product.At(i, j) = sum;
		}
	}

	return product;

}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {

	//std::cout << "copy assign" << name << "\n";
	delete[] arr;

	n = other.height();
	m = other.width();
	size = n * m;

	arr = new T[size];

	for (unsigned i = 0; i < n; i++)
	{
		for (unsigned j = 0; j < m; j++)
		{
			At(i, j) = other.peek(i, j);
		}

	}


	return *this;
}


template<typename T>
Matrix<T> Matrix<T>::identity() const {
	Matrix<T> id = Matrix(n, m);

	unsigned i = 0;
	while (i < n && i < m)
	{
		id.At(i, i) = 1;
		i++;
	}
	id.name = "deleteme";
	return id;
}

template<typename T>
void Matrix<T>::Print() const{
	//std::string str;
	for (unsigned i = 0; i < n; i++)
	{
		for (unsigned j = 0; j < m; j++)
		{
			//str.clear();
			//str = At(i, j);
			//str += ';';
			std::cout << std::setw(10) << peek(i, j);
		}
		std::cout << "\n";
	}
}



template<typename T>
unsigned Matrix<T>::height() const{
	return n;
}


template<typename T>
unsigned Matrix<T>::width() const {
	return m;
}

template<typename T>
unsigned Matrix<T>::get_index(unsigned i, unsigned j) const {
	return i * m + j;
}

//template<typename T>
//Matrix<T>::operator std::string() {
//	std::string str;
//	for (unsigned i = 0; i < n; i++)
//	{
//		for (unsigned j = 0; j < m; j++)
//		{
//			str += arr[get_index(i, j)] + ";";
//		}
//		str += '\n';
//	}
//}

//template<typename T>
//std::ostream& operator<<(std::ostream& os, Matrix<T> const& m) {
//	os << m.height() << " " << m.width();
//	return os;
//}


#endif // !MATRIX_CPP