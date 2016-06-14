#include "stdafx.h"
#include "Circle.h"

using boost::math::double_constants::pi;


CCircle::CCircle(int x, int y, int radius, std::string const& borderColor, std::string const& color)
	: m_centrePoint(x, y, color)
	, m_x(x)
	, m_y(y)
	, m_radius(radius > 0 ? radius : 0)
	, m_borderColor(borderColor)
	, m_color(color)
{
}

std::string CCircle::ToString() const
{
	std::stringstream stream;
	stream << "Circle <" << m_centrePoint.GetX() << "," << m_centrePoint.GetY() << ">, R=" << m_radius;
	stream << ", P=" << GetPerimeter() << ", S=" << GetArea();
	return stream.str();
}

double CCircle::GetPerimeter() const
{
	return (2 * pi * m_radius);
}

double CCircle::GetArea() const
{
	return (pi * pow(m_radius, 2));
}

std::string CCircle::GetBorderColor() const
{
	return m_borderColor;
}

std::string CCircle::GetColor() const
{
	return m_color;
}

CCircle::~CCircle()
{
}
