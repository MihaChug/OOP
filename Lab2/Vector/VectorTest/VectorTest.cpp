#include "stdafx.h"
#include "../Vector/vectorProcessor.h"

BOOST_AUTO_TEST_SUITE(ProcessVectorTest)

BOOST_AUTO_TEST_CASE(emptyVector)
{
	std::vector<double> emptyVector;
	MaxMultMinDiv(emptyVector);
	BOOST_CHECK(emptyVector.empty());
};

BOOST_AUTO_TEST_CASE(does_not_change)
{
	std::vector<double> number = { 1, 1 };
	MaxMultMinDiv(number);
	std::vector<double> realVec = { 1,1 };
	BOOST_CHECK_EQUAL_COLLECTIONS(number.begin(), number.end(),
		realVec.begin(), realVec.end());
};

BOOST_AUTO_TEST_CASE(max_more_zero_min_less_zero)
{
	std::vector<double> number = { -1, 0, 1, 2, 3, 4, 5 };
	MaxMultMinDiv(number);
	std::vector<double> realVec = { 5, 0, -5, -10, -15, -20, -25 };
	BOOST_CHECK_EQUAL_COLLECTIONS(number.begin(), number.end(),
		realVec.begin(), realVec.end());
};


BOOST_AUTO_TEST_CASE(max_more_zero_min_more_zero)
{
	std::vector<double> number = { 1, 2, 3, 4, 5 };
	MaxMultMinDiv(number);
	std::vector<double> realVec = { 5, 10, 15, 20, 25 };
	BOOST_CHECK_EQUAL_COLLECTIONS(number.begin(), number.end(),
		realVec.begin(), realVec.end());
};

BOOST_AUTO_TEST_CASE(max_less_zero_min_less_zero)
{
	std::vector<double> number = { -1, -2};
	MaxMultMinDiv(number);
	std::vector<double> realVec = {-0.5, -1 };
	BOOST_CHECK_EQUAL_COLLECTIONS(number.begin(), number.end(),
		realVec.begin(), realVec.end());
};

BOOST_AUTO_TEST_CASE(min_equal_zero)
{
	std::vector<double> number = { 0, 1, 2, 3, 4, 5 };
	MaxMultMinDiv(number);
	std::vector<double> realVec = {0, 5, 10, 15, 20, 25 };
	BOOST_CHECK_EQUAL_COLLECTIONS(number.begin(), number.end(),
		realVec.begin(), realVec.end());
};

BOOST_AUTO_TEST_SUITE_END()
