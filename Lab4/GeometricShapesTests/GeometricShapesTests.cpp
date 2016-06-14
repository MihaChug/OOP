#include "stdafx.h"
#include "..\GeometricShapes\IShape.h"
#include "..\GeometricShapes\Point.h"
#include "..\GeometricShapes\LineSegment.h"
#include "..\GeometricShapes\Circle.h"
#include "..\GeometricShapes\Triangle.h"
#include "..\GeometricShapes\Rectangle.h"


BOOST_AUTO_TEST_SUITE(Point)
	BOOST_AUTO_TEST_CASE(can_be_generated)
	{
		boost::optional <CPoint> point = CPoint(0, 0, "#00ff00");
		BOOST_CHECK(point);
	}
	BOOST_AUTO_TEST_CASE(has_zero_perimeter_and_area)
	{
		CPoint point(1, 1, "#00ff00");
		BOOST_CHECK_EQUAL(point.GetArea(), 0);
		BOOST_CHECK_EQUAL(point.GetPerimeter(), 0);
	}
	BOOST_AUTO_TEST_CASE(has_correct_info_about_himself)
	{
		CPoint point(1, 1, "#00ff00");
		BOOST_CHECK_EQUAL(point.ToString(), "Point <1,1>, P=0, S=0");
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(LineSegment)
	BOOST_AUTO_TEST_CASE(can_be_generated)
	{
		boost::optional <CLineSegment> line = CLineSegment(0, 0, 0, 2, "#00ff00");
		BOOST_CHECK(line);
	}
	BOOST_AUTO_TEST_CASE(has_perimeter_equal_his_length_and_zero_area)
	{
		CLineSegment line(1, 1, 1, 4, "#00ff00");
		BOOST_CHECK_EQUAL(line.GetArea(), 0);
		BOOST_CHECK_EQUAL(line.GetPerimeter(), 3);
	}
	BOOST_AUTO_TEST_CASE(has_correct_info_about_himself)
	{
		CLineSegment line(0, 0, 0, 2, "#00ff00");
		BOOST_CHECK_EQUAL(line.ToString(), "Line Segment <<0,0><0,2>>, P=2, S=0");
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle)
	BOOST_AUTO_TEST_CASE(can_be_generated)
	{
		boost::optional <CCircle> circle = CCircle(0, 0, 10, "#00ff00", "#00ff00");
		BOOST_CHECK(circle);
	}
	BOOST_AUTO_TEST_CASE(has_true_perimeter_and_area)
	{
		CCircle circle(10, 10, 10, "#00ff00", "#00ff00");
		BOOST_CHECK_EQUAL(round(circle.GetArea() * 100000)/100000., 314.15927);
		BOOST_CHECK_EQUAL(round(circle.GetPerimeter() * 100000) / 100000., 62.83185);
	}
	BOOST_AUTO_TEST_CASE(has_correct_info_about_himself)
	{
		CCircle circle(10, 10, 10, "#00ff00", "#00ff00");
		BOOST_CHECK_EQUAL(circle.ToString(), "Circle <10,10>, R=10, P=62.8319, S=314.159");
	}
	BOOST_AUTO_TEST_CASE(can_not_have_negative_radius)
	{
		CCircle circle(10, 10, -5, "#00ff00", "#00ff00");
		BOOST_CHECK_EQUAL(circle.ToString(), "Circle <10,10>, R=0, P=0, S=0");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rectangle)
	BOOST_AUTO_TEST_CASE(can_be_generated)
	{
		boost::optional <CRectangle> rect = CRectangle(0, 5, 10, 5, "#00ff00", "#00ff00");
		BOOST_CHECK(rect);
	}
	BOOST_AUTO_TEST_CASE(has_true_perimeter_and_area)
	{
		CRectangle rect(0, 0, 10, 10, "#00ff00", "#00ff00");
		BOOST_CHECK_EQUAL(rect.GetArea(), 100);
		BOOST_CHECK_EQUAL(rect.GetPerimeter(), 40);
	}
	BOOST_AUTO_TEST_CASE(has_correct_info_about_himself)
	{
		CRectangle rect(10, 8, 4, 2, "#00ff00", "#00ff00");
		BOOST_CHECK_EQUAL(rect.ToString(), "Rectangle <10,8>, W=4, H=2, P=12, S=8");
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Triangle)
	BOOST_AUTO_TEST_CASE(can_be_generated)
	{
		boost::optional <CTriangle> triangle = CTriangle(0, 8, 1, 2, 4, 6, "#00ff00", "#00ff00");
		BOOST_CHECK(triangle);
	}
	BOOST_AUTO_TEST_CASE(has_true_perimeter_and_area)
	{
		CTriangle triangle(0, 0, 0, 3, 4, 0, "#00ff00", "#00ff00");
		BOOST_CHECK_EQUAL(triangle.GetArea(), 6);
		BOOST_CHECK_EQUAL(triangle.GetPerimeter(), 12);
	}
	BOOST_AUTO_TEST_CASE(has_correct_info_about_himself)
	{
		CTriangle triangle(0, 0, 0, 3, 4, 0, "#00ff00", "#00ff00");
		BOOST_CHECK_EQUAL(triangle.ToString(), "Triangle <<0,0><0,3><4,0>>, P=12, S=6");
	}
BOOST_AUTO_TEST_SUITE_END()