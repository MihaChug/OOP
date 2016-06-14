#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(int x, int y, int width, int height, std::string const& borderColor, std::string const& color)
	: m_vertex(x, y, borderColor)
	, m_width(width > 0 ? width : 0)
	, m_height(height > 0 ? height : 0)
	, m_borderColor(borderColor)
	, m_color(color)
{
}

std::string CRectangle::ToString() const
{
	std::stringstream stream;
	stream << "Rectangle <" << m_vertex.GetX() << "," << m_vertex.GetY() << ">, W=" << m_width << ", H=" << m_height;
	stream << ", P=" << GetPerimeter() << ", S=" << GetArea();
	return stream.str();
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

std::string CRectangle::GetBorderColor() const
{
	return m_borderColor;
}

std::string CRectangle::GetColor() const
{
	return m_color;
}
