#pragma once
#include "SolidShape.h"
#include "Point.h"
#include "LineSegment.h"

class CTriangle final : public ISolidShape
{
public:
	CTriangle(int x1, int y1, 
		int x2, int y2, 
		int x3, int y3, 
		std::string const& borderColor, std::string const& color);

	std::string ToString()const override;
	double GetPerimeter()const override;
	double GetArea()const override;
	std::string GetBorderColor()const override;
	std::string GetColor()const override;
	~CTriangle() = default;
private:
	CPoint m_firstVertex;
	CPoint m_secondVertex;
	CPoint m_thirdVertex;
	double m_firstSide;
	double m_secondSide;
	double m_thirdSide;
	std::string m_borderColor;
	std::string m_color;
};

