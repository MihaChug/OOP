#pragma once
#include "IShape.h"
#include "Point.h"
#include "LineSegment.h"
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"

class COperationsWithShapes
{
public:
	COperationsWithShapes(std::istream & input, std::ostream & output, std::vector<std::shared_ptr<IShape>> & shapes);
	bool HandleCommand();
	void SortByPerimeter();
	void SortByArea();
	void GetInfoAndSort();
	std::shared_ptr<IShape> GetPointPtr(std::istream & strm);
	std::shared_ptr<IShape> GetLinePtr(std::istream & strm);
	std::shared_ptr<IShape> GetCirclePtr(std::istream & strm);
	std::shared_ptr<IShape> GetRectanglePtr(std::istream & strm);
	std::shared_ptr<IShape> GetTrianglePtr(std::istream & strm);
	~COperationsWithShapes();
private:
	std::istream & m_input;
	std::ostream & m_output;
	std::vector<std::shared_ptr<IShape>> m_shapes;
	typedef std::map<std::string, std::function<std::shared_ptr<IShape>(std::istream & args)>> ShapesMap;
	const ShapesMap m_shapesMap;
};

