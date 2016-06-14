#include "stdafx.h"
#include "../Rational/Rational.h"

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}

/*
Рациональное число:
равно нулю по умолчанию (0/1)
может быть созданно из целого в формате (n / 1)
может быть задано с указанием числителя и знаменателя
хранится в нормализованном виде
*/

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

void VerifyRational(const std::pair<int, CRational> const& rational, int expectedIntegerPart, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(rational.first, expectedIntegerPart);
	BOOST_CHECK_EQUAL((rational.second).GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL((rational.second).GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
BOOST_AUTO_TEST_CASE(is_0_by_default)
{
	VerifyRational(CRational(), 0, 1);
}
BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
{
	VerifyRational(CRational(10), 10, 1);
	VerifyRational(CRational(-10), -10, 1);
	VerifyRational(CRational(0), 0, 1);
}
BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
{
	VerifyRational(CRational(5, 2), 5, 2);
	VerifyRational(CRational(-5, 2), -5, 2);
	VerifyRational(CRational(5, -2), -5, 2);
	VerifyRational(CRational(-5, -2), 5, 2);
}
BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
{
	VerifyRational(CRational(6, 8), 3, 4);
	VerifyRational(CRational(6, -8), -3, 4);
	VerifyRational(CRational(-6, 8), -3, 4);
	VerifyRational(CRational(-6, -8), 3, 4);
	VerifyRational(CRational(-10, 20), -1, 2);
}
BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
{
	BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
}
// Возвращает представление рационального числа в виде смешанной дроби
BOOST_AUTO_TEST_CASE(can_be_returned_in_the_form_of_a_mixed_fraction)
{
	VerifyRational(CRational(15, 2).ToCompoundFraction(), 7, 1, 2);
	VerifyRational(CRational(-9, 4).ToCompoundFraction(), -2, 1, 4);
	VerifyRational(CRational(1, 2).ToCompoundFraction(), 0, 1, 2);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
// Возвращает отношение числителя и знаменателя в виде числа double
//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(can_return_the_ratio_of_the_numerator_and_denominator)
{
	BOOST_CHECK_EQUAL(CRational(3, 5).ToDouble(), 0.6);
	BOOST_CHECK_EQUAL(CRational(-2, 10).ToDouble(), -0.2);
	BOOST_CHECK_EQUAL(CRational(0, 10).ToDouble(), 0);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
// Указание: см. материалы к лекции
// Пример использования:
//	const CRational r1(3, 5);
//	CRational r2 = -r1; // r2 должно стать -3/5
//	assert(r2.GetNumerator(), -3);
//	assert(r2.GetDenominator(), 5);
//	CRational r3 = +r2; // r3 также равно -3/5
//	assert(r3.GetNumerator(), -3);
//	assert(r3.GetDenominator(), 5);
// Унарный минус возвращает раицональное число без знака
// Унарный плюс возвращает рациональное число, равное текущему
// Реализация не должна допускать операции вроде:
//  -someRational = someOtherRational;
//	+someRational = someOtherRational;
//////////////////////////////////////////////////////////////////////////
struct unaryOperationFixture
{
	CRational rational1;
	unaryOperationFixture()
		: rational1(3, 5)
	{}
};

BOOST_FIXTURE_TEST_SUITE(unary_operation, unaryOperationFixture)
BOOST_AUTO_TEST_CASE(unary_plus)
{
	auto r2 = +rational1;
	BOOST_CHECK_EQUAL(r2.GetNumerator(), 3);
	BOOST_CHECK_EQUAL(r2.GetDenominator(), 5);
}
BOOST_AUTO_TEST_CASE(unary_minus)
{
	auto r3 = -rational1;
	BOOST_CHECK_EQUAL(r3.GetNumerator(), -3);
	BOOST_CHECK_EQUAL(r3.GetDenominator(), 5);
}
BOOST_AUTO_TEST_CASE(unary_plus_with_unary_minus)
{
	auto r2 = -rational1;
	auto r3 = +r2;
	BOOST_CHECK_EQUAL(r3.GetNumerator(), -3);
	BOOST_CHECK_EQUAL(r3.GetDenominator(), 5);
}
BOOST_AUTO_TEST_CASE(unary_minus_with_unary_minus)
{
	auto r2 = -rational1;
	auto r3 = -r2;
	BOOST_CHECK_EQUAL(r3.GetNumerator(), 3);
	BOOST_CHECK_EQUAL(r3.GetDenominator(), 5);
}
BOOST_AUTO_TEST_SUITE_END()



// TODO: 3. Реализовать бинарный +
BOOST_AUTO_TEST_CASE(can_be_realize_the_binary_summ)
{
	VerifyRational(CRational(1, 2) + CRational(1, 6), 2, 3);
	VerifyRational(CRational(1, 2) + CRational(1), 3, 2);
	VerifyRational(CRational(1) + CRational(1, 2), 3, 2);
}
// TODO: 4. Реализовать бинарный -
BOOST_AUTO_TEST_CASE(can_be_realize_the_binary_minus)
{
	VerifyRational(CRational(1, 2) - CRational(1, 6), 1, 3);
	VerifyRational(CRational(1, 2) - CRational(1), -1, 2);
	VerifyRational(CRational(1) - CRational(1, 2), 1, 2);
}
////////////////////////////////////////////////////////
struct binaryOperationFixture
{
	CRational rational;
	binaryOperationFixture()
		: rational(1, 2)
	{}
};
BOOST_FIXTURE_TEST_SUITE(binary_operation, binaryOperationFixture)
// TODO: 5. Реализовать оператор +=
BOOST_AUTO_TEST_CASE(can_be_changed_after_summ_with_the_other_rational)
{
	rational += CRational(1, 6);
	VerifyRational(rational, 2, 3);
}
BOOST_AUTO_TEST_CASE(can_be_changed_after_summ_with_int)
{
	rational += CRational(1);
	VerifyRational(rational, 3, 2);
}
// TODO: 6. Реализовать оператор -=
BOOST_AUTO_TEST_CASE(can_be_changed_after_minus_with_the_other_rational)
{
	rational -= CRational(1, 6);
	VerifyRational(rational, 1, 3);
}
BOOST_AUTO_TEST_CASE(can_be_changed_after_minus_with_int)
{
	rational -= CRational(1);
	VerifyRational(rational, -1, 2);
}
BOOST_AUTO_TEST_SUITE_END()
// TODO: 7. Реализовать оператор *
BOOST_AUTO_TEST_CASE(could_be_multiplied_by_another_rational_or_integer_number)
{
	VerifyRational(CRational(1, 2) * CRational(2, 3), 1, 3);
	VerifyRational(CRational(1, 2) * CRational(-3), -3, 2);
	VerifyRational(CRational(7) * CRational(2, 3), 14, 3);
}
// TODO: 8. Реализовать оператор /
BOOST_AUTO_TEST_CASE(could_be_dividen_into_another_rational_or_integer_number)
{
	VerifyRational(CRational(1, 2) / CRational(2, 3), 3, 4);
	VerifyRational(CRational(1, 2) / CRational(5), 1, 10);
	VerifyRational(CRational(7) / CRational(2, 3), 21, 2);
}
//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
// Умножает значение первого рационального числа на другое рациональное, 
//	либо целое:
//	(1/2) *= (2/3) → (1/3)
//	(1/2) *= 3     → (3/2)
//////////////////////////////////////////////////////////////////////////
BOOST_FIXTURE_TEST_SUITE(multiplied_operation, binaryOperationFixture)
BOOST_AUTO_TEST_CASE(with_another_rational)
{
	rational *= CRational(2, 3);
	VerifyRational(rational, 1, 3);
}
BOOST_AUTO_TEST_CASE(with_integer)
{
	rational *= CRational(3);
	VerifyRational(rational, 3, 2);
}
BOOST_AUTO_TEST_SUITE_END()



//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////
BOOST_FIXTURE_TEST_SUITE(divided_operation, binaryOperationFixture)
BOOST_AUTO_TEST_CASE(into_another_rational)
{
	rational /= CRational(2, 3);
	VerifyRational(rational, 3, 4);
}
BOOST_AUTO_TEST_CASE(into_integer)
{
	rational /= CRational(3);
	VerifyRational(rational, 1, 6);
}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(could_be_compared_by_equal)
{
	BOOST_CHECK(CRational(1, 2) == CRational(1, 2));
	BOOST_CHECK(CRational(4, 1) == CRational(4));
	BOOST_CHECK(CRational(3) == CRational(3, 1));
	BOOST_CHECK(CRational(1, 2) != CRational(2, 3));
	BOOST_CHECK(CRational(1, 2) != CRational(7));
	BOOST_CHECK(CRational(3) != CRational(2, 3));
}
//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
// Сравнивают два рациональных числа, рациональное с целым, 
//	целое с рациональным:
//	(1/2) >= (1/3) → true
//	(1/2) <= (1/3) → false
//	(3/1) > 2      → true
//	(1/2) < 7      → true
//	3 <= (7/2)     → true
//	3 >= (8/2)     → false
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(can_be_comparison_with_another_number)
{
	BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
	BOOST_CHECK(!(CRational(1, 2) <= CRational(1, 3)));
	BOOST_CHECK(CRational(3, 1) > CRational(2));
	BOOST_CHECK(CRational(1, 2) < CRational(7));
	BOOST_CHECK(CRational(3) <= CRational(7, 2));
	BOOST_CHECK(!(CRational(3) >= CRational(8, 2)));
}

//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////

struct ostreamOperatorFixture
{
	CRational rational = CRational(7, 15);
};

BOOST_FIXTURE_TEST_SUITE(ostream_operator, ostreamOperatorFixture)

BOOST_AUTO_TEST_CASE(rational_integer_to_ostream)
{
	std::ostringstream strm;
	strm << rational;
	BOOST_CHECK_EQUAL(strm.str(), "7/15");
}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////

struct istreamOperatorFixture
{
	CRational rational;
};

BOOST_FIXTURE_TEST_SUITE(istream_operator, istreamOperatorFixture)

BOOST_AUTO_TEST_CASE(rational_integer_in_istream)
{
	std::istringstream strm("7/15");
	strm >> rational;
	VerifyRational(rational, 7, 15);
}

BOOST_AUTO_TEST_CASE(negative_rational_integer_in_istream)
{
	std::istringstream strm("-7/15");
	strm >> rational;
	VerifyRational(rational, -7, 15);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()