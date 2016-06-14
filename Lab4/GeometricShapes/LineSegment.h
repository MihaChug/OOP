#pragma once
#include "IShape.h"
#include "Point.h"


class CLineSegment final : public IShape
{
public:
	CLineSegment(int x1, int y1, int x2, int y2, std::string const& borderColor);
	std::string ToString()const override;
	double GetArea()const override;
	double GetPerimeter()const override;
	std::string GetBorderColor()const override;
	~CLineSegment() = default;
private:
	CPoint m_beginPoint;
	CPoint m_endPoint;
	double m_length;
	std::string m_borderColor;
};

