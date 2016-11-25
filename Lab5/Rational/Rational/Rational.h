#pragma once
#include <sstream>
#include <cmath>
/*
Класс, моделирующий рациональное число
*/
class CRational final
{
public:
	CRational(int numerator = 0, int denominator = 1);

	// Возвращает представление рационального числа в виде смешанной дроби
	std::pair<int, CRational>ToCompoundFraction()const;

	// Возвращает числитель
	int GetNumerator() const;

	// Возвращает знаменатель
	int GetDenominator() const;

	double ToDouble()const;

	// 1) Унарный + и -
	CRational const operator-()const;

	CRational const operator+()const;
	//

	// 4) +=
	CRational& operator +=(CRational const& rValue);
	//

	// 5) -=
	CRational &operator -=(CRational const &rValue);
	//

	// 8) *=
	CRational &operator *=(CRational const &rValue);
	//

	// 9) /=
	CRational &operator /=(CRational const &rValue);
	//

private:

	int m_numerator;
	int m_denominator;

	// Нормализует рациональное число
	void Normalize();
};

// 2) Binary +
CRational const operator +(CRational const &rational1, CRational const &rational2);
//

// 3) Binary -
CRational const operator -(CRational const &rational1, CRational const &rational2);
//

// 6) *
CRational const operator *(CRational const &rational1, CRational const &rational2);
//

// 7) /
CRational const operator /(CRational const &rational1, CRational const &rational2);
//

// 10) == and !=
bool const operator ==(CRational const &rational1, CRational const &rational2);

bool const operator !=(CRational const &rational1, CRational const &rational2);
//

// 11) <, <=, >, >=
bool const operator <(CRational const &rational1, CRational const &rational2);

bool const operator <=(CRational const &rational1, CRational const &rational2);

bool const operator >(CRational const &rational1, CRational const &rational2);

bool const operator >=(CRational const &rational1, CRational const &rational2);
//

// 12) ostream << 
std::ostream & operator <<(std::ostream & strm, CRational const & rational);
//

// 13) istream >>
std::istream & operator >> (std::istream & strm, CRational & rational);
//

// Вычисляет наибольший общий знаменатель чисел a и b
unsigned GCD(unsigned a, unsigned b);