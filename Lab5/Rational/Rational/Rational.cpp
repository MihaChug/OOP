#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <stdexcept>


CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integerPart = m_numerator / m_denominator;
	return{ integerPart, CRational(abs(m_numerator - integerPart * m_denominator), m_denominator) };
}


void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
//////////////////////////////////////////////////////////////////////////

double CRational::ToDouble() const
{
	return (double)m_numerator / (double)m_denominator;
}


//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}



//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator+(CRational const & rational) const
{
	int resultDenominator = rational.GetDenominator() * GetDenominator();
	int resultNumerator = GetNumerator() * (resultDenominator / GetDenominator()) + rational.GetNumerator() * (resultDenominator / rational.GetDenominator());
	return CRational(resultNumerator, resultDenominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator-(CRational const & rational) const
{
	int resultDenominator = rational.GetDenominator() * GetDenominator();
	int resultNumerator = GetNumerator() * (resultDenominator / GetDenominator()) - rational.GetNumerator() * (resultDenominator / rational.GetDenominator());
	return CRational(resultNumerator, resultDenominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
//////////////////////////////////////////////////////////////////////////

void CRational::operator+=(CRational const & rational)
{
	*this = *this + rational;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
//////////////////////////////////////////////////////////////////////////

void CRational::operator-=(CRational const & rational)
{
	*this = *this - rational;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator*(CRational const & rational) const
{
	return CRational(GetNumerator() * rational.GetNumerator(), GetDenominator() * rational.GetDenominator());
}

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator/(CRational const & rational) const
{
	return CRational(GetNumerator() * rational.GetDenominator(), GetDenominator() * rational.GetNumerator());
}

//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
//////////////////////////////////////////////////////////////////////////

void CRational::operator*=(CRational const & rational)
{
	*this = *this * rational;
}


//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////

void CRational::operator/=(CRational const & rational)
{
	*this = *this / rational;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////


bool const CRational::operator == (CRational const & rational) const
{
	return (GetNumerator() == rational.GetNumerator()) && (GetDenominator() == rational.GetDenominator());
}

bool const CRational::operator!=(CRational const & rational) const
{
	return !(GetNumerator() == rational.GetNumerator()) || (GetDenominator() == rational.GetDenominator());
}

//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
//////////////////////////////////////////////////////////////////////////

bool const CRational::operator<(CRational const& rational)const
{
	return (GetNumerator() * rational.GetDenominator() < rational.GetNumerator() * GetDenominator());
}

bool const CRational::operator<=(CRational const& rational)const
{
	return (GetNumerator() * rational.GetDenominator() <= rational.GetNumerator() * GetDenominator());
}

bool const CRational::operator>(CRational const& rational)const
{
	return (GetNumerator() * rational.GetDenominator() > rational.GetNumerator() * GetDenominator());
}

bool const CRational::operator>=(CRational const& rational)const
{
	return (GetNumerator() * rational.GetDenominator() >= rational.GetNumerator() * GetDenominator());
}


//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////
std::istream & operator >> (std::istream & stream, CRational & rational)
{
	int numerator;
	int denominator;

	if ((stream >> numerator) && (stream.get() == '/') && (stream >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		stream.setstate(stream.rdstate() | std::ios_base::failbit);
	}
	return stream;
}

std::ostream & operator<<(std::ostream & stream, CRational const & rational)
{
	stream << rational.GetNumerator() << "/" << rational.GetDenominator();
	return stream;
}
