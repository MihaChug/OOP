#include "stdafx.h"
#include "..\Vector\vectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

// Функция ProcessVector
BOOST_AUTO_TEST_SUITE(MaxMultMinDiv_function)

// Создает пустой вектор из пустого вектора
BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
{
	vector<double> emptyVector;
	MaxMultMinDiv(emptyVector);
	BOOST_CHECK(emptyVector.empty());
}

// не изменяет содержимое вектора
BOOST_AUTO_TEST_CASE(does_not_change)
{
	vector<double> numbers = { 5, 5, 5 };
	auto copy(numbers); // аналог vector<double> copy(numbers);
	MaxMultMinDiv(numbers);
	BOOST_CHECK(numbers == copy);
}

BOOST_AUTO_TEST_SUITE(min_elem_less_zero_max_elem_more_zero)
BOOST_AUTO_TEST_CASE(should_multy_on_max_and_dic_on_min)
{
	vector<double> numbers = { -1, 0, 1, 2, 3 };
	MaxMultMinDiv(numbers);

	BOOST_CHECK(VectorsAreEqual(numbers,
	{ (-1 * 3 / -1), (0 * 3 / -1), (1 * 3 / -1), (2 * 3 / -1), (3 * 3 / -1) }
	));
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(min_elem_more_zero_max_elem_more_zero)
BOOST_AUTO_TEST_CASE(should_multy_on_max_and_dic_on_min)
{
	vector<double> numbers = { 1, 2, 3, 4, 5 };
	MaxMultMinDiv(numbers);

	BOOST_CHECK(VectorsAreEqual(numbers,
	{ (1 * 5 / 1), (2 * 5 / 1), (3 * 5 / 1), (4 * 5 / 1), (5 * 5 / 1) }
	));
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(min_elem_less_zero_max_elem_less_zero)
BOOST_AUTO_TEST_CASE(should_multy_on_max_and_dic_on_min)
{
	vector<double> numbers = { -1, -2, -3, -4, -5 };
	MaxMultMinDiv(numbers);

	BOOST_CHECK(VectorsAreEqual(numbers,
	{ (-1 * -5 / -1), (-2 * -5 / -1), (-3 * -5 / -1), (-4 * -5 / -1), (-5 * -5 / -1) }
	));
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(min_elem_equal_zero)
BOOST_AUTO_TEST_CASE(should_multy_on_max_and_dic_on_min)
{
	vector<double> numbers = { 0, 1, 2, 3, 4, 5 };
	MaxMultMinDiv(numbers);

	BOOST_CHECK(VectorsAreEqual(numbers,
	{(0), (1 * 5 / 1), (2 * 5 / 1), (3 * 5 / 1), (4 * 5 / 1), (5 * 5 / 1) }
	));
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()