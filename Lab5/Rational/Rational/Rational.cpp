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
// TODO: 1. ����������� ����� ToDouble() �������� �������
//////////////////////////////////////////////////////////////////////////

double CRational::ToDouble() const
{
	return (double)m_numerator / (double)m_denominator;
}


//////////////////////////////////////////////////////////////////////////
// TODO: 2. ����������� ������� + � ������� -
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
// TODO: 3. ����������� �������� +
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator+(CRational const & rational) const
{
	int resultDenominator = rational.GetDenominator() * GetDenominator();
	int resultNumerator = GetNumerator() * (resultDenominator / GetDenominator()) + rational.GetNumerator() * (resultDenominator / rational.GetDenominator());
	return CRational(resultNumerator, resultDenominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 4. ����������� �������� -
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator-(CRational const & rational) const
{
	int resultDenominator = rational.GetDenominator() * GetDenominator();
	int resultNumerator = GetNumerator() * (resultDenominator / GetDenominator()) - rational.GetNumerator() * (resultDenominator / rational.GetDenominator());
	return CRational(resultNumerator, resultDenominator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 5. ����������� �������� +=
//////////////////////////////////////////////////////////////////////////

void CRational::operator+=(CRational const & rational)
{
	*this = *this + rational;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 6. ����������� �������� -=
//////////////////////////////////////////////////////////////////////////

void CRational::operator-=(CRational const & rational)
{
	*this = *this - rational;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 7. ����������� �������� *
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator*(CRational const & rational) const
{
	return CRational(GetNumerator() * rational.GetNumerator(), GetDenominator() * rational.GetDenominator());
}

//////////////////////////////////////////////////////////////////////////
// TODO: 8. ����������� �������� /
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator/(CRational const & rational) const
{
	return CRational(GetNumerator() * rational.GetDenominator(), GetDenominator() * rational.GetNumerator());
}

//////////////////////////////////////////////////////////////////////////
// TODO: 9. ����������� �������� *=
//////////////////////////////////////////////////////////////////////////

void CRational::operator*=(CRational const & rational)
{
	*this = *this * rational;
}


//////////////////////////////////////////////////////////////////////////
// TODO: 10. ����������� �������� /=
//////////////////////////////////////////////////////////////////////////

void CRational::operator/=(CRational const & rational)
{
	*this = *this / rational;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 11. ����������� ��������� == � !=
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
// TODO: 12. ����������� ��������� <, >, <=, >=
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
// TODO: 13. ����������� �������� ������ ������������� ����� � �������� ����� 
//	std::ostream � ������� <���������>/<�����������>, 
//	��������: 7/15
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// TODO: 14. ����������� �������� ����� ������������� ����� �� �������� ������ 
//	std::istream � ������� <���������>/<�����������>, 
//	��������: 7/15
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
