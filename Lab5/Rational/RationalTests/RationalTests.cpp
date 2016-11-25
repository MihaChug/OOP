// task1tests.cpp : Defines the entry point for the console application.
//

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

void VerifyCompoundFraction(const CRational &r, int expectedInteger, int expectedNumerator, int expectedDeniminator)
{
	BOOST_CHECK_EQUAL(r.ToCompoundFraction().first, expectedInteger);
	BOOST_CHECK_EQUAL(r.ToCompoundFraction().second.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.ToCompoundFraction().second.GetDenominator(), expectedDeniminator);
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


	// 1) unary -
	BOOST_AUTO_TEST_CASE(unary_minus_returns_rational_integer_with_opposite_sign)
	{
		VerifyRational(-CRational(2, 3), -2, 3);
		VerifyRational(-CRational(-2, 3), 2, 3);
		VerifyRational(-CRational(-2, -3), -2, 3);
	}

	// 1) unary +
	BOOST_AUTO_TEST_CASE(unary_plus_returns_rational_integer_equal_to_current)
	{
		VerifyRational(+CRational(2, 3), 2, 3);
		VerifyRational(+CRational(-2, 3), -2, 3);
		VerifyRational(+CRational(2, -3), -2, 3);
	}


	// 2) binary +
	struct binary_addition_
	{
		CRational rational = CRational(1, 2);
	};
	
	BOOST_FIXTURE_TEST_SUITE(binary_addition, binary_addition_)
		
		BOOST_AUTO_TEST_CASE(addition_of_two_floating_point_integers)
		{
			auto answer = rational + CRational(5, 6);
			VerifyRational(answer, 4, 3);
		}
	
		BOOST_AUTO_TEST_CASE(addition_of_fractional_and_integer)
		{
			auto answer = rational + 1;
			VerifyRational(answer, 3, 2);
		}
	
		BOOST_AUTO_TEST_CASE(addition_of_rational_and_fractional_integerss)
		{
			auto answer = 1 + rational;
			VerifyRational(answer, 3, 2);
		}
		
	BOOST_AUTO_TEST_SUITE_END()
	//

	// 3) Binary -
	struct binary_subtraction_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(binary_subtraction, binary_subtraction_)

		BOOST_AUTO_TEST_CASE(subtraction_of_two_floating_point_integers)
		{
			auto answer = rational - CRational(3, 8);
			VerifyRational(answer, 1, 8);
		}

		BOOST_AUTO_TEST_CASE(subtraction_of_fractional_and_rational_integers)
		{
			auto answer = rational - 1;
			VerifyRational(answer, -1, 2);
		}

		BOOST_AUTO_TEST_CASE(subtraction_of_rational_and_fractional_integers)
		{
			auto answer = 1 - rational;
			VerifyRational(answer, 1, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()
	//
	
	// 4) +=
	struct addition_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(addition, addition_)

		BOOST_AUTO_TEST_CASE(addition_floating_point_integer)
		{
			rational += CRational(1, 6);
			VerifyRational(rational, 2, 3);
		}

		BOOST_AUTO_TEST_CASE(addition_integer)
		{
			rational += 1;
			VerifyRational(rational, 3, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()
	//

	// 5) -=
	struct subtraction_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(subtraction, subtraction_)

		BOOST_AUTO_TEST_CASE(subtraction_floating_point_integer)
		{
			rational -= CRational(1, 6);
			VerifyRational(rational, 1, 3);
		}

		BOOST_AUTO_TEST_CASE(subtraction_integer)
		{
			rational -= 1;
			VerifyRational(rational, -1, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()
	//

	// 6) *
	struct bi_multiplication_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(bi_multiplication, bi_multiplication_)

		BOOST_AUTO_TEST_CASE(bi_multiplication_rational_integers)
		{
			auto answer = rational * CRational(2, 3);
			VerifyRational(answer, 1, 3);
		}

		BOOST_AUTO_TEST_CASE(bi_multiplication_rational_and_integer)
		{
			auto answer = rational * CRational(-3);
			VerifyRational(answer, -3, 2);
		}

		BOOST_AUTO_TEST_CASE(bi_multiplication_integer_and_rational)
		{
			auto answer = CRational(20) * rational;
			VerifyRational(answer, 10, 1);
		}

	BOOST_AUTO_TEST_SUITE_END()
	//

	// 7) /
	struct bi_division_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(bi_division, bi_division_)

		BOOST_AUTO_TEST_CASE(bi_division_rational_integers)
		{
			auto answer = rational / CRational(2, 3);
			VerifyRational(answer, 3, 4);
		}

		BOOST_AUTO_TEST_CASE(bi_division_rational_and_integer)
		{
			auto answer = rational / CRational(5);
			VerifyRational(answer, 1, 10);
		}

		BOOST_AUTO_TEST_CASE(bi_division_integer_and_rational)
		{
			auto answer = CRational(7) / rational;
			VerifyRational(answer, 14, 1);
		}

		BOOST_AUTO_TEST_CASE(can_not_bi_divide_rational_and_zero)
		{
			BOOST_REQUIRE_THROW(auto answer = rational / CRational(0), std::invalid_argument::exception);

			BOOST_REQUIRE_THROW(auto answer = rational / CRational(0, 1), std::invalid_argument::exception);
		}



	BOOST_AUTO_TEST_SUITE_END()
	//

	// 8) *=
	struct multiplication_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(multiplication, multiplication_)

		BOOST_AUTO_TEST_CASE(multiplication_floating_point_integer)
		{
			rational *= CRational(2, 3);
			VerifyRational(rational, 1, 3);
		}

		BOOST_AUTO_TEST_CASE(multiplication_integer)
		{
			rational *= 3;
			VerifyRational(rational, 3, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()
	//

	// 9) /=
	struct division_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(division, division_)

		BOOST_AUTO_TEST_CASE(division_floating_point_integer)
		{
			rational /= CRational(2, 3);
			VerifyRational(rational, 3, 4);
		}

		BOOST_AUTO_TEST_CASE(division_integer)
		{
			rational /= 3;
			VerifyRational(rational, 1, 6);
		}

		BOOST_AUTO_TEST_CASE(can_not_divide_rational_and_zero)
		{
			BOOST_REQUIRE_THROW(rational /= CRational(0), std::invalid_argument);
		}

	BOOST_AUTO_TEST_SUITE_END()
	//

	// 10) == and !=
	struct equality_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(equality, equality_)

		BOOST_AUTO_TEST_CASE(equality_rational_integers)
		{
			BOOST_CHECK(rational == CRational(1, 2));

			BOOST_CHECK(!(rational == CRational(2, 3)));
		}

		BOOST_AUTO_TEST_CASE(equality_rational_and_integer)
		{
			BOOST_CHECK(!(rational == CRational(7)));
		}

		BOOST_AUTO_TEST_CASE(equality_integer_and_rational)
		{
			BOOST_CHECK(CRational(3) == CRational(3, 1));
		}

		BOOST_AUTO_TEST_CASE(equality_two_integers)
		{
			BOOST_CHECK(CRational(4, 1) == CRational(4));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct inequality_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(inequality, inequality_)

		BOOST_AUTO_TEST_CASE(inequality_rational_integers)
		{
			BOOST_CHECK(!(rational != CRational(1, 2)));

			BOOST_CHECK(rational != CRational(2, 3));
		}

		BOOST_AUTO_TEST_CASE(inequality_rational_and_integer)
		{
			BOOST_CHECK(rational != CRational(7));
		}

		BOOST_AUTO_TEST_CASE(inequality_integer_and_rational)
		{
			BOOST_CHECK(!(CRational(3) != CRational(3, 1)));
		}

		BOOST_AUTO_TEST_CASE(inequality_two_integers)
		{
			BOOST_CHECK(!(CRational(4, 1) != CRational(4)));
		}

	BOOST_AUTO_TEST_SUITE_END()
	//

	// 11) <, <=, >, >=
	struct less_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(less, less_)

		BOOST_AUTO_TEST_CASE(less_rational_integers)
		{
			BOOST_CHECK(!(rational < CRational(1, 2)));

			BOOST_CHECK(!(CRational(2, 3) < rational));
		}

		BOOST_AUTO_TEST_CASE(less_rational_and_integer)
		{
			BOOST_CHECK(rational < CRational(7));
		}

		BOOST_AUTO_TEST_CASE(less_integer_and_rational)
		{
			BOOST_CHECK(!(CRational(3) < CRational(3, 1)));
		}

		BOOST_AUTO_TEST_CASE(less_two_integers)
		{
			BOOST_CHECK(!(CRational(4, 1) < CRational(4)));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct less_or_equality_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(less_or_equality, less_or_equality_)

		BOOST_AUTO_TEST_CASE(less_or_equality_rational_integers)
		{
			BOOST_CHECK((rational <= CRational(1, 2)));

			BOOST_CHECK(!(CRational(2, 3) <= rational));
		}

		BOOST_AUTO_TEST_CASE(less_or_equality_rational_and_integer)
		{
			BOOST_CHECK(rational <= CRational(7));
		}

		BOOST_AUTO_TEST_CASE(less_or_equality_integer_and_rational)
		{
			BOOST_CHECK(CRational(3) <= CRational(3, 1));
		}

		BOOST_AUTO_TEST_CASE(less_or_equality_two_integers)
		{
			BOOST_CHECK(CRational(4, 1) <= CRational(4));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct larger_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(larger, larger_)

		BOOST_AUTO_TEST_CASE(larger_rational_integers)
		{
			BOOST_CHECK(!(rational > CRational(1, 2)));

			BOOST_CHECK((CRational(2, 3) > rational));
		}

		BOOST_AUTO_TEST_CASE(larger_rational_and_integer)
		{
			BOOST_CHECK(!(rational > CRational(7)));
		}

		BOOST_AUTO_TEST_CASE(larger_integer_and_rational)
		{
			BOOST_CHECK(!(CRational(3) > CRational(3, 1)));
		}

		BOOST_AUTO_TEST_CASE(larger_two_integers)
		{
			BOOST_CHECK(!(CRational(4, 1) > CRational(4)));
		}

	BOOST_AUTO_TEST_SUITE_END()
	
	struct larger_or_equality_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(larger_or_equality, larger_or_equality_)

		BOOST_AUTO_TEST_CASE(larger_or_equality_rational_integers)
		{
			BOOST_CHECK((rational >= CRational(1, 2)));

			BOOST_CHECK((CRational(2, 3) >= rational));
		}

		BOOST_AUTO_TEST_CASE(larger_or_equality_rational_and_integer)
		{
			BOOST_CHECK(!(rational >= CRational(7)));
		}

		BOOST_AUTO_TEST_CASE(larger_or_equality_integer_and_rational)
		{
			BOOST_CHECK(CRational(3) >= CRational(3, 1));
		}

		BOOST_AUTO_TEST_CASE(larger_or_equality_two_integers)
		{
			BOOST_CHECK(CRational(4, 1) >= CRational(4));
		}

	BOOST_AUTO_TEST_SUITE_END()
	//

	// 12) ostream <<
	struct ostream_
	{
		CRational rational = CRational(1, 2);
	};

	BOOST_FIXTURE_TEST_SUITE(ostream, ostream_)

		BOOST_AUTO_TEST_CASE(rational_integer_to_ostream)
		{
			std::ostringstream strm;
			strm << rational;
			BOOST_CHECK_EQUAL(strm.str(), "1/2");
		}

	BOOST_AUTO_TEST_SUITE_END()

	// 13) istream <<
	struct istream_
	{
		CRational rational;
	};

	BOOST_FIXTURE_TEST_SUITE(istream, istream_)

		BOOST_AUTO_TEST_CASE(rational_integer_in_istream)
		{
			std::istringstream strm("1/2");
			strm >> rational;
			VerifyRational(rational, 1, 2);
		}
		
		BOOST_AUTO_TEST_CASE(negative_rational_integer_in_istream)
		{
			std::istringstream strm("-1/2");
			strm >> rational;
			VerifyRational(rational, -1, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()
	//

	//ADDITION TASK TESTS;
	BOOST_AUTO_TEST_CASE(can_get_compound_fraction)
	{
		auto rational = CRational(9, 4);
		VerifyCompoundFraction(rational, 2, 1, 4);
	}

	BOOST_AUTO_TEST_CASE(can_get_compound_negative_fraction)
	{
		auto rational = CRational(-9, 4);
		VerifyCompoundFraction(rational, -2, -1, 4);
	}

	BOOST_AUTO_TEST_CASE(integer_will_return_to_previous_state)
	{
		auto rational = CRational(-9);
		VerifyCompoundFraction(rational, -9, 0, 1);
	}

	BOOST_AUTO_TEST_CASE(if_fraction_is_less_than_zero_then_integer_equal_to_zero)
	{
		auto rational = CRational(1, 2);
		VerifyCompoundFraction(rational, 0, 1, 2);
	}

BOOST_AUTO_TEST_SUITE_END()
