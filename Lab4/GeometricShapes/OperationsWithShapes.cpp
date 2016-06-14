#include "stdafx.h"
#include "OperationsWithShapes.h"

using namespace std;
using namespace std::placeholders;

COperationsWithShapes::COperationsWithShapes(istream & input, ostream & output, std::vector<shared_ptr<IShape>> & shapes)
	: m_input(input)
	, m_output(output)
	, m_shapes(shapes)
	, m_shapesMap({
		{ "point", bind(&COperationsWithShapes::GetPointPtr, this, _1) },
		{ "line", bind(&COperationsWithShapes::GetLinePtr, this, _1) },
		{ "circle", bind(&COperationsWithShapes::GetCirclePtr, this, _1) },
		{ "rectangle", bind(&COperationsWithShapes::GetRectanglePtr, this, _1) },
		{ "triangle", bind(&COperationsWithShapes::GetTrianglePtr, this, _1) },
})
{
}

void COperationsWithShapes::SortByPerimeter() 
{
	std::sort(m_shapes.begin(), m_shapes.end(), [](std::shared_ptr<IShape> & first, std::shared_ptr<IShape> & second)
	{
		return first->GetPerimeter() > second->GetPerimeter();
	});
}

void COperationsWithShapes::SortByArea() {
	std::sort(m_shapes.begin(), m_shapes.end(), [](std::shared_ptr<IShape> & first, std::shared_ptr<IShape> & second)
	{
		return first->GetArea() < second->GetArea();
	});
}

void COperationsWithShapes::GetInfoAndSort()
{
	m_output << "Sorting by increasing the areas:\n" << endl;
	SortByArea();
	for (auto it : m_shapes)
	{
		m_output << it->ToString() << endl;
	}
	cout << endl << endl << "Sorting by reduce the perimeters:\n" << endl;
	SortByPerimeter();
	for (auto it : m_shapes)
	{
		m_output << it->ToString() << endl;
	}
}

bool COperationsWithShapes::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);
	string shape;
	strm >> shape;
	auto it = m_shapesMap.find(shape);
	if (it != m_shapesMap.end())
	{
		m_shapes.push_back(it->second(strm));
	}
	else if (shape == "end")
	{
		GetInfoAndSort();
	}
	else if (shape == "Help")
	{
		cout << "List of shapes and parameters:" << endl;
		cout << "Point: X, Y, Border Color" << endl;
		cout << "Line: Begin X, Begin Y, End X, End Y, Border Color" << endl;
		cout << "Circle: X, Y, Radius, Border Color, Color" << endl;
		cout << "Triangle: X1, Y1, X2, Y2, X3, Y3, Border Color, Color" << endl;
		cout << "Rectangle: X, Y, Width, Height, Border Color, Color" << endl;
		cout << "Example: rectangle 20 30 17 25 #ff0000 #00ff00" << endl << endl;                     

	}
	else
	{
		return false;
	}
	return true;
}

std::shared_ptr<IShape> COperationsWithShapes::GetPointPtr(istream & strm)
{
	int x, y;
	strm >> x >> y;
	string borderColor;
	strm >> borderColor;
	return make_shared<CPoint>(CPoint(x, y, borderColor));
}

std::shared_ptr<IShape> COperationsWithShapes::GetLinePtr(std::istream & strm)
{
	int beginX, beginY, endX, endY;
	strm >> beginX >> beginY >> endX >> endY;
	string borderColor;
	strm >> borderColor;
	return make_shared<CLineSegment>(CLineSegment(beginX, beginY, endX, endY, borderColor));
}

std::shared_ptr<IShape> COperationsWithShapes::GetCirclePtr(std::istream & strm)
{
	int x, y, radius;
	strm >> x >> y >> radius;
	string borderColor, color;
	strm >> borderColor >> color;
	return make_shared<CCircle>(CCircle(x, y, radius, borderColor, color));
}

std::shared_ptr<IShape> COperationsWithShapes::GetRectanglePtr(std::istream & strm)
{
	int x, y, w, h;
	strm >> x >> y >> w >> h;
	string borderColor, color;
	strm >> borderColor >> color;
	return make_shared<CRectangle>(CRectangle(x, y, w, h, borderColor, color));
}

std::shared_ptr<IShape> COperationsWithShapes::GetTrianglePtr(std::istream & strm)
{
	int x1, y1, x2, y2, x3, y3;
	strm >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	string borderColor, color;
	strm >> borderColor >> color;
	return make_shared<CTriangle>(CTriangle(x1, y1, x2, y2, x3, y3, borderColor, color));
}

COperationsWithShapes::~COperationsWithShapes()
{
}

