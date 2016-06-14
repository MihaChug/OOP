#include "stdafx.h"
#include "Point.h"


CPoint::CPoint(int x, int y, std::string const& borderColor)
	: m_x(x)
	, m_y(y)
	, m_borderColor(borderColor)
{
};

int CPoint::GetX() const
{
	return m_x;
}

int CPoint::GetY() const
{
	return m_y;
}

std::string CPoint::ToString() const
{
	std::stringstream stream;
	stream << "Point <" << m_x << "," << m_y << ">";
	stream << ", P=" << GetPerimeter() << ", S=" << GetArea();
	return stream.str();
}

double CPoint::GetArea() const
{
	return 0;
}

double CPoint::GetPerimeter() const
{
	return 0;
}

std::string CPoint::GetBorderColor() const
{
	return m_borderColor;
}

