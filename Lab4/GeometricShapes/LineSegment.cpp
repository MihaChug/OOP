#include "stdafx.h"
#include "LineSegment.h"


CLineSegment::CLineSegment(int x1, int y1, int x2, int y2, std::string const& borderColor)
	: m_beginPoint(x1, y1, borderColor)
	, m_endPoint(x2, y2, borderColor)
	, m_borderColor(borderColor)
{
	m_length = sqrt(pow((m_endPoint.GetX() - m_beginPoint.GetX()), 2) + pow((m_endPoint.GetY() - m_beginPoint.GetY()), 2));
}

std::string CLineSegment::ToString() const
{
	std::stringstream stream;
	stream << "Line Segment <<" << m_beginPoint.GetX() << "," << m_beginPoint.GetY() << "><" << m_endPoint.GetX() << "," << m_endPoint.GetY() << ">>";
	stream << ", P=" << GetPerimeter() << ", S=" << GetArea();
	return stream.str();
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return m_length;
}

std::string CLineSegment::GetBorderColor() const
{
	return m_borderColor;
}
