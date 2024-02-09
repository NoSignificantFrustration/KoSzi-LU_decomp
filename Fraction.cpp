
#include "Fraction.h"



Fraction::Fraction() : numerator(0), denominator(1), sign(true){ }
Fraction::Fraction(int numerator) : Fraction(int_abs(numerator), 1, numerator >= 0){ }

Fraction::Fraction(int numerator, int denominator) : Fraction(int_abs(numerator), int_abs(denominator), numerator <= 0 == denominator <= 0) { }

Fraction::Fraction(uint1024_t numerator, uint1024_t denominator, bool sign) : numerator(numerator), denominator(denominator), sign(sign) {
	if (denominator == 0)
	{
		throw std::invalid_argument("Zero in denominator");
	}
}

uint1024_t Fraction::int_abs(int val) const {

	return val >= 0 ? (uint1024_t)val : (uint1024_t)-val;
}

void Fraction::Scale(uint1024_t scale) {
	if (scale == 0)
	{
		throw std::invalid_argument("Scaling to zero, zero in denominator");
	}

	numerator *= scale;
	denominator *= scale;
}

Fraction Fraction::scaled(uint1024_t scale) const {
	return Fraction(numerator * scale, denominator * scale, sign);
}

Fraction Fraction::reciprocal() const {
	return Fraction(denominator, numerator, sign);
}

uint1024_t Fraction::GCD(uint1024_t a, uint1024_t b) {
	if (b == 0 || a == 0)
	{
		return 1;
	}
	if (a < b)
	{
		uint1024_t tmp = a;
		a = b;
		b = tmp;
	}

	uint1024_t remainder = a % b;
	if (remainder == 0)
	{
		return b;
	}

	return GCD(b, remainder);
}

uint1024_t Fraction::LCD(uint1024_t a, uint1024_t b) {
	return a * b / GCD(a, b);
}


void Fraction::Simplify() {
	if (numerator == 0)
	{
		denominator = 1;
		sign = true;
		return;
	}

	uint1024_t gcd = GCD(numerator, denominator);
	if (gcd > 1)
	{
		numerator /= gcd;
		denominator /= gcd;
	}
	
	if (numerator == 0)
	{
		sign = true;
	}
}

Fraction::operator std::string() const {
	return std::string((!sign ? "-" : "") + numerator.str() + (denominator == 1 ? "" : "/" + denominator.str()));
}

float Fraction::to_float() const {
	using boost::numeric_cast;
	using boost::bad_numeric_cast;

	using LongFloat = boost::multiprecision::cpp_bin_float_quad;
	float f = (LongFloat(numerator) / LongFloat(denominator)).convert_to<float>();

	return sign ? f : -f;
}

std::string Fraction::to_string(const Fraction& f) const {
	return std::to_string(to_float());
}

std::ostream& operator<<(std::ostream& os, const Fraction& f)
{
	os << (std::string)f;
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& f) {
	int val;
	is >> val;
	f = val;

	return is;
}

Fraction Fraction::operator =(int val) {
	sign = val >= 0;
	numerator = int_abs(val);
	denominator = 1;
	return *this;
}

bool Fraction::operator ==(int val) const{
	if (denominator != 1 || val >= 0 != sign)
	{
		return false;
	}

	return int_abs(val) == numerator;

}

Fraction Fraction::operator-() const {
	return Fraction(numerator, denominator, !sign);
}

Fraction Fraction::operator +(const Fraction& f) const {
	
	Fraction out = *this;
	out += f;
	return out;
}

Fraction Fraction::operator +=(const Fraction& f) {

	uint1024_t lcd = denominator;
	uint1024_t a = numerator;
	uint1024_t b = f.numerator;

	if (denominator != f.denominator)
	{
		 lcd = LCD(denominator, f.denominator);

		 a = lcd / denominator * numerator;
		 b = lcd / f.denominator * f.numerator;
	}
	

	//There is most likely a better way to do this

	if (sign == f.sign)
	{
		numerator = a + b;
		denominator = lcd;
		Simplify();
		return *this;
	}

	if (a == b)
	{
		numerator = 0;
		denominator = 1;
		sign = true;
		return *this;
	}
	denominator = lcd;

	if (a > b)
	{
		numerator = a - b;
		Simplify();
		return *this;
	}

	numerator = b - a;
	sign = !sign;
	Simplify();

	return *this;

}

Fraction Fraction::operator -(const Fraction& f) const {

	Fraction out = *this;
	out -= f;
	return out;
}

Fraction Fraction::operator -=(const Fraction& f) {
	uint1024_t lcd = LCD(denominator, f.denominator);

	uint1024_t a = lcd / denominator * numerator;
	uint1024_t b = lcd / f.denominator * f.numerator;

	//There is most likely a better way to do this
	if (sign == f.sign)
	{
		if (a == b)
		{
			numerator = 0;
			denominator = 1;
			sign = true;
			return *this;
		}
		denominator = lcd;

		if (a > b)
		{
			numerator = a - b;
			Simplify();
			return *this;
		}

		numerator = b - a;
		sign = !sign;
		Simplify();
		return *this;

		
	}

	numerator = a + b;
	denominator = lcd;
	Simplify();
	return *this;

}


Fraction Fraction::operator *(const Fraction& f) const {
	Fraction out = Fraction(numerator * f.numerator, denominator * f.denominator, sign == f.sign);
	out.Simplify();
	return out;
}

Fraction Fraction::operator *=(const Fraction& f) {

	numerator *= f.numerator;
	denominator *= f.denominator;
	sign = sign == f.sign;
	Simplify();
	return *this;
}

Fraction Fraction::operator /(const Fraction& f) const {
	if (f.numerator == 0)
	{
		throw std::invalid_argument("Division by zero");
	}
	Fraction out = *this * f.reciprocal();

	return out;
}

Fraction Fraction::operator /=(const Fraction& f) {
	if (f.numerator == 0)
	{
		throw std::invalid_argument("Division by zero");
	}
	*this *= f.reciprocal();
	
	return *this;
}
