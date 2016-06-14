#include "SolidShape.h"
#include "Point.h"

class CCircle final : public ISolidShape
{
public:
	CCircle(int x, int y, int radius, std::string const& borderColor, std::string const& color);
	
	std::string ToString()const override;
	double GetPerimeter()const override;
	double GetArea()const override;
	std::string GetBorderColor()const override;
	std::string GetColor()const override;
	~CCircle();
private:
	CPoint m_centrePoint;
	int m_x;
	int m_y;
	double m_radius;
	std::string m_borderColor;
	std::string m_color;
};

