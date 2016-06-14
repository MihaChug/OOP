#include "stdafx.h"
#include "Triangle.h"



CTriangle::CTriangle(int x1, int y1, int x2, int y2, int x3, int y3, std::string const& borderColor, std::string const& color)
	: m_firstVertex(x1, y1, borderColor)
	, m_secondVertex(x2, y2, borderColor)
	, m_thirdVertex(x3, y3, borderColor)
	, m_borderColor(borderColor)
	, m_color(color)

{
	m_firstSide = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	m_secondSide = sqrt(pow((x3 - x2), 2) + pow((y3- y2), 2));
	m_thirdSide = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
}

std::string CTriangle::ToString() const
{
	std::stringstream stream;
	stream << "Triangle <<" << m_firstVertex.GetX() << "," << m_firstVertex.GetY() << ">";
	stream << "<" << m_secondVertex.GetX() << "," << m_secondVertex.GetY() << ">";
	stream << "<" << m_thirdVertex.GetX() << "," << m_thirdVertex.GetY() << ">>";
	stream << ", P=" << GetPerimeter() << ", S=" << GetArea();
	return stream.str();
}

double CTriangle::GetPerimeter() const
{
	return (m_firstSide + m_secondSide + m_thirdSide);
}

double CTriangle::GetArea() const
{
	double p = GetPerimeter() / 2;
	return sqrt(p * (p - m_firstSide) * (p - m_secondSide) * (p - m_thirdSide));
}

std::string CTriangle::GetBorderColor() const
{
	return m_borderColor;
}

std::string CTriangle::GetColor() const
{
	return m_color;
}