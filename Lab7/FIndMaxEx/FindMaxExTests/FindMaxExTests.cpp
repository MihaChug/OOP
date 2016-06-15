// FindMaxExTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../FIndMaxEx/FindMaxEx.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(FindMax_Tests)

	struct SportMansVector
	{
		std::vector<std::shared_ptr<SportsMan>> sportsmansVector = {
			std::make_shared<SportsMan>("Filipp", "Azisovich", "Kirkorov", 216.5, 50.3),
			std::make_shared<SportsMan>("Baskov", "Djigurhanyanov", "Nikolay", 100.5, 21.5),
			std::make_shared<SportsMan>("Albert", "Shamilevich", "Djigarhanyan", 167, 214)
		};
	};
	BOOST_FIXTURE_TEST_SUITE(find_max_paramathers_in_sportmans_vector, SportMansVector)
		BOOST_AUTO_TEST_CASE(find_sportsman_with_max_height)
		{
			std::shared_ptr<SportsMan> sportsman;
			BOOST_CHECK(FindMax(sportsmansVector, sportsman, [](const auto sportsman1, const auto sportsman2) {
				return sportsman1->height < sportsman2->height;
			}));
			BOOST_CHECK_EQUAL(sportsman->height, 216.5);
		}
		BOOST_AUTO_TEST_CASE(find_sportsman_with_max_weight)
		{
			std::shared_ptr<SportsMan> sportsman;
			FindMax(sportsmansVector, sportsman, [](const auto sportsman1, const auto sportsman2) {
				return sportsman1->weight < sportsman2->weight;
			});
			BOOST_CHECK_EQUAL(sportsman->weight, 214);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct Object
	{
		Object(std::string const &str)
			: str(str)
		{};
		virtual std::string const &GetString()const
		{
			return str;
		}
	private:
		std::string str;
	};
	struct MockObjWithExcept
		: public Object
	{
		MockObjWithExcept(std::string const &str)
			: Object(str)
		{};
		std::string const &GetString()const override
		{
			throw std::exception("Test exception.");
		}
	};
	struct MockObjWithOutExcept
		: public Object
	{
		MockObjWithOutExcept(std::string const &str)
			: Object(str)
		{};
	};
	struct MockObjectsVector
	{
		std::vector<std::shared_ptr<Object>> vec = {
			std::make_shared<MockObjWithOutExcept>("a"),
			std::make_shared<MockObjWithOutExcept>("b")
		};
		std::shared_ptr<Object> max;
	};
	BOOST_FIXTURE_TEST_SUITE(commit_or_rollback_tests, MockObjectsVector)
		BOOST_AUTO_TEST_CASE(can_find_max_element_if_no_except)
		{
			BOOST_CHECK(FindMax(vec, max, [](const auto obj1, const auto obj2) {
				return obj1->GetString() < obj2->GetString();
			}));
			BOOST_CHECK_EQUAL(max->GetString(), "b");
		}
		BOOST_AUTO_TEST_CASE(if_find_max_process_throw_except_then_func_return_false_end_max_elem_not_change)
		{
			BOOST_CHECK(FindMax(vec, max, [](const auto obj1, const auto obj2) {
				return obj1->GetString() < obj2->GetString();
			}));
			BOOST_CHECK_EQUAL(max->GetString(), "b");
			vec.push_back(std::make_shared<MockObjWithExcept>("zzz"));
			BOOST_REQUIRE_THROW(FindMax(vec, max, [](const auto obj1, const auto obj2) {
				return obj1->GetString() < obj2->GetString();
			}), std::exception);
			BOOST_CHECK_EQUAL(max->GetString(), "b");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()