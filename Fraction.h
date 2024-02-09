#pragma once
#include <stdexcept>
#include <string>
#include <ostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

using namespace boost::multiprecision;

struct Fraction {
public:
	//0: -, 1: +
	bool sign;

	uint1024_t numerator;
	uint1024_t denominator;

	Fraction();
	Fraction(int numerator);
	Fraction(int numerator, int denominator);
	Fraction(uint1024_t numerator, uint1024_t denominator, bool sign = true);

	void Scale(uint1024_t scale);
	Fraction scaled(uint1024_t scale) const;
	
	Fraction reciprocal() const;

	Fraction operator =(int val);
	bool operator ==(int val) const;
	Fraction operator -() const;
	Fraction operator +(const Fraction& f) const;
	Fraction operator +=(const Fraction& f);
	Fraction operator -(const Fraction& f) const;
	Fraction operator -=(const Fraction& f);
	Fraction operator *(const Fraction& f) const;
	Fraction operator *=(const Fraction& f);
	Fraction operator /(const Fraction& f) const;
	Fraction operator /=(const Fraction& f);

	operator std::string() const;
	float to_float() const;
	std::string to_string(const Fraction& f) const;
	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
	friend std::istream& operator>>(std::istream& is, Fraction& f);

private:
	//Greatest common diviser
	uint1024_t GCD(uint1024_t a, uint1024_t b);
	//Least common denominator
	uint1024_t LCD(uint1024_t a, uint1024_t b);
	void Simplify();
	uint1024_t int_abs(int) const;

};