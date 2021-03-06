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

std::pair<int, CRational> CRational::ToCompoundFraction()const
{
	int integer = static_cast<int>(ToDouble());
	int numerator = m_numerator - m_denominator * integer;

	return std::make_pair<int, CRational>(std::move(integer), CRational(numerator, m_denominator));
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble()const
{
	return m_numerator / m_denominator;
}

CRational const CRational::operator-()const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const CRational::operator+()const
{
	return *this;
}

CRational &CRational::operator+=(CRational const &rValue)
{
	*this = *this + rValue;
	return *this;
}

CRational &CRational::operator-=(CRational const &rValue)
{
	*this = *this - rValue;
	return *this;
}

CRational & CRational::operator*=(CRational const & rValue)
{
	*this = *this * rValue;
	return *this;
}

CRational & CRational::operator/=(CRational const & rValue)
{
	*this = *this / rValue;
	return *this;
}

CRational const operator *(CRational const &rational1, CRational const &rational2)
{
	return (CRational(rational1.GetNumerator() * rational2.GetNumerator()
		, rational1.GetDenominator() * rational2.GetDenominator()));
}

CRational const operator +(CRational const &rational1, CRational const &rational2)
{
	return (CRational((rational1.GetNumerator() * rational2.GetDenominator())
		+ (rational2.GetNumerator() * rational1.GetDenominator()),
		rational1.GetDenominator() * rational2.GetDenominator()));
}

CRational const operator -(CRational const &rational1, CRational const &rational2)
{
	return rational1 + -rational2;
}

CRational const operator /(CRational const &rational1, CRational const &rational2)
{
	return (CRational(rational1.GetNumerator() * rational2.GetDenominator()
		, rational1.GetDenominator() * rational2.GetNumerator()));
}

bool const operator ==(CRational const &rational1, CRational const &rational2)
{
	return (rational1.GetNumerator() == rational2.GetNumerator()
		&& (rational1.GetDenominator() == rational2.GetDenominator()));
}

bool const operator !=(CRational const &rational1, CRational const &rational2)
{
	return !(rational1 == rational2);
}

bool const operator <(CRational const &rational1, CRational const &rational2)
{
	return (rational1.GetNumerator() * rational2.GetDenominator()
		< rational2.GetNumerator() * rational1.GetDenominator());
}

bool const operator <=(CRational const &rational1, CRational const &rational2)
{
	return (rational1 == rational2) || (rational1 < rational2);
}

bool const operator >(CRational const &rational1, CRational const &rational2)
{
	return !(rational1 <= rational2);
}

bool const operator >=(CRational const &rational1, CRational const &rational2)
{
	return (rational1 == rational2) || (rational1 > rational2);
}

std::ostream & operator <<(std::ostream & strm, CRational const & rational)
{
	strm << rational.GetNumerator() << '/' << rational.GetDenominator();
	return strm;
}

std::istream & operator >> (std::istream & strm, CRational & rational)
{
	std::streamoff startPos = strm.tellg();
	int numerator;
	int denominator;
	if ((strm >> numerator) && (strm.get() == '/') && (strm >> denominator))
	{
		rational = CRational(numerator, denominator);
		return strm;
	}
	strm.seekg(startPos);
	return strm;
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




//////////////////////////////////////////////////////////////////////////
// TODO: 2. ����������� ������� + � ������� -
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 3. ����������� �������� +
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 4. ����������� �������� -
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 5. ����������� �������� +=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 6. ����������� �������� -=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 7. ����������� �������� *
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 8. ����������� �������� /
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 9. ����������� �������� *=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 10. ����������� �������� /=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 11. ����������� ��������� == � !=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 12. ����������� ��������� <, >, <=, >=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 13. ����������� �������� ������ ������������� ����� � �������� ����� 
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
// TODO: 14. ����������� �������� ����� ������������� ����� �� �������� ������ 
//////////////////////////////////////////////////////////////////////////


