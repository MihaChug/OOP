#include "stdafx.h"
#include "../StringList/StringList.h"

using namespace std;

struct NoExceptMockObj
{

};


struct MockObjWithExceptions : public NoExceptMockObj
{
	MockObjWithExceptions& operator=(std::string && str)
	{
		throw std::invalid_argument("Test Exception");
	}
};

struct EmptyStringList
{
	CStringList<std::string> list;
};

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)
// проверить отсутствие исключений при создании пустого списка
// проверить валидность данных после вызова перемещающего оператора, который выбросит исключение
BOOST_AUTO_TEST_SUITE(when_created)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(list.GetSize(), 0u);
			BOOST_CHECK(list.IsEmpty());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_appeding_a_string)
		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.GetSize();
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.Append("goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "goodbye");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.Append("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(after_add_a_string_to_front)
		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.GetSize();
			list.AddToFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.AddToFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetFrontElement_method)
		{
			list.AddToFront("hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			list.AddToFront("goodbye");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "goodbye");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.AddToFront("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetFrontElement()));
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}
		BOOST_AUTO_TEST_CASE(after_decrement_saved_end_pos_iter_it_return_added_element)
		{
			auto end = list.end();
			list.Append("sample");
			BOOST_CHECK_EQUAL(*--list.end(), "sample");
		}
		BOOST_AUTO_TEST_CASE(derefference_incremented_rend_iterator_returns_last_element)
		{
			list.Append("sample");
			BOOST_CHECK_EQUAL(*(list.rbegin()), "sample");
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct FilledStringList
		: EmptyStringList
	{
		FilledStringList()
		{
			list.Append("Hello, ");
			list.Append("World!");
			list.Append("It's");
			list.Append("me, ");
			list.Append("Lack of sleep.");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(after_filled_the_string_list, FilledStringList)

		struct IteratorEndTests : FilledStringList
		{
			CStringList<std::string>::CIterator end = list.end();
		};

		BOOST_FIXTURE_TEST_SUITE(can_take_an_iterator_to_next_of_the_last_item, IteratorEndTests)
			BOOST_AUTO_TEST_CASE(attempt_to_dereference_leads_to_throw_except)
			{
				BOOST_REQUIRE_THROW(*end, std::runtime_error);
			}
			BOOST_AUTO_TEST_CASE(you_add_an_item_to_value_of_iterator_will_not_change)
			{
				list.Append("String");
				BOOST_CHECK(end == list.end());
			}
			BOOST_AUTO_TEST_CASE(attempt_to_increment_end_iterator_pos_throw_exception)
			{
				BOOST_REQUIRE_THROW(++end, std::runtime_error);
			}
			BOOST_AUTO_TEST_CASE(one_time_decrement_end_iterator_pos_returns_iterator_with_last_element)
			{
				BOOST_CHECK_EQUAL(*(--end), "Lack of sleep.");
			}
		BOOST_AUTO_TEST_SUITE_END()
	
		struct ClearedStringList : FilledStringList
		{
			ClearedStringList()
			{
				list.Clear();
			}
		};
		BOOST_FIXTURE_TEST_SUITE(after_clear_a_string_list, ClearedStringList)
			BOOST_AUTO_TEST_CASE(list_is_empty)
			{
				BOOST_CHECK(list.IsEmpty());
			}
			BOOST_AUTO_TEST_CASE(list_size_is_equal_zero)
			{
				BOOST_CHECK_EQUAL(list.GetSize(), 0);
			}
			BOOST_AUTO_TEST_CASE(can_clear_already_empty_list_with_no_throw)
			{
				BOOST_REQUIRE_NO_THROW(list.Clear());
			}
			BOOST_AUTO_TEST_CASE(attempt_to_get_front_element_throw_exception)
			{
				BOOST_REQUIRE_THROW(list.GetFrontElement(), std::runtime_error);
			}
			BOOST_AUTO_TEST_CASE(attempt_to_get_back_element_throw_exception)
			{
				BOOST_REQUIRE_THROW(list.GetBackElement(), std::runtime_error);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_FIXTURE_TEST_SUITE(can_insert_data_in_iterator_pos, FilledStringList)
			BOOST_AUTO_TEST_CASE(element_is_inserted_before_iterator_position)
			{
				BOOST_CHECK_EQUAL(list.GetFrontElement(), "Hello, ");
				BOOST_REQUIRE_NO_THROW(list.Insert(list.begin(), "Hm..."));
				BOOST_CHECK_EQUAL(list.GetFrontElement(), "Hm...");
			}
			BOOST_AUTO_TEST_CASE(inserting_incremented_list_size)
			{
				auto oldSize = list.GetSize();
				BOOST_REQUIRE_NO_THROW(list.Insert(list.begin(), "String"));
				BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
				BOOST_REQUIRE_NO_THROW(list.Insert(list.begin(), "Ptn"));
				BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
			}
			BOOST_AUTO_TEST_CASE(can_insert_element_in_any_pos)
			{
				BOOST_CHECK_EQUAL(*(++list.begin()), "World!");
				BOOST_REQUIRE_NO_THROW(list.Insert(++list.begin(), "Or Welkome in?"));
				BOOST_CHECK_EQUAL(*(++list.begin()), "Or Welkome in?");
			}
			BOOST_AUTO_TEST_CASE(can_insert_before_end_iter_pos)
			{
				BOOST_CHECK_EQUAL(list.GetBackElement(), "Lack of sleep.");
				BOOST_REQUIRE_NO_THROW(list.Insert(list.end(), "What?"));
				BOOST_CHECK_EQUAL(*(--list.end()), "What?");
				BOOST_CHECK_EQUAL(list.GetBackElement(), "What?");
			}
			BOOST_AUTO_TEST_CASE(can_insert_to_empty_list)
			{
				CStringList<std::string> emptyList;
				BOOST_CHECK_NO_THROW(emptyList.Insert(emptyList.begin(), "123"));
				BOOST_CHECK_EQUAL(emptyList.GetFrontElement(), "123");
				BOOST_CHECK_EQUAL(emptyList.GetBackElement(), "123");
			}
			BOOST_AUTO_TEST_CASE(cant_insert_to_nullptr)
			{
				BOOST_REQUIRE_THROW(list.Insert(CStringList<std::string>::CIterator(), "crash!"), std::invalid_argument);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_FIXTURE_TEST_SUITE(can_erase_data_in_iterator_pos, FilledStringList)
			BOOST_AUTO_TEST_CASE(do_not_erase_end_iter_pos)
			{
				BOOST_REQUIRE_THROW(list.Erase(list.end()), std::runtime_error);
			}
			BOOST_AUTO_TEST_CASE(erase_method_returns_iterator_on_next_element)
			{
				auto it = list.begin();
				BOOST_CHECK_EQUAL(*it, "Hello, ");
				BOOST_REQUIRE_NO_THROW(list.Erase(it));
			}
			BOOST_AUTO_TEST_CASE(erase_first_element_change_first_element_to_next)
			{
				auto it = list.begin();
				BOOST_CHECK_EQUAL(*it, "Hello, ");
				BOOST_REQUIRE_NO_THROW(list.Erase(it));
				BOOST_CHECK_EQUAL(*it, "World!");
				BOOST_CHECK_EQUAL(list.GetFrontElement(), "World!");
			}
			BOOST_AUTO_TEST_CASE(erase_last_element_returns_null_iter)
			{
				auto it = --list.end();
				BOOST_CHECK_EQUAL(list.GetBackElement(), "Lack of sleep.");
				BOOST_REQUIRE_NO_THROW(list.Erase(it));
				BOOST_REQUIRE_THROW(*it, std::runtime_error);
				BOOST_CHECK_EQUAL(list.GetBackElement(), "me, ");
			}
			BOOST_AUTO_TEST_CASE(erase_decrementing_list_size)
			{
				auto oldSize = list.GetSize();
				BOOST_REQUIRE_NO_THROW(list.Erase(list.begin()));
				BOOST_CHECK_EQUAL(list.GetSize(), oldSize - 1);
				BOOST_REQUIRE_NO_THROW(list.Erase(--list.end()));
				BOOST_CHECK_EQUAL(list.GetSize(), oldSize - 2);
			}
			BOOST_AUTO_TEST_CASE(dont_erase_it_from_empty_list)
			{
				CStringList<std::string> emptyList;
				BOOST_REQUIRE_THROW(emptyList.Erase(emptyList.begin()), std::runtime_error);
				BOOST_REQUIRE_THROW(emptyList.Erase(emptyList.end()), std::runtime_error);
			}
			BOOST_AUTO_TEST_CASE(can_erase_it_from_other_pos_and_it_switch_to_next_element)
			{
				auto it = list.begin();
				++it; ++it; ++it;
				BOOST_CHECK_EQUAL(*it, "me, ");
				BOOST_REQUIRE_NO_THROW(list.Erase(it));
				BOOST_CHECK_EQUAL(*it, "Lack of sleep.");
			}
			BOOST_AUTO_TEST_CASE(erase_of_a_single_element_in_begin_does_not_make_list_of_invalid)
			{
				CStringList<double> list2;
				list2.Append(1.1);
				BOOST_REQUIRE_NO_THROW(list2.Erase(list2.begin()));
				list2.Append(2.2);
				BOOST_CHECK_EQUAL(list2.GetBackElement(), 2.2);
				BOOST_CHECK_EQUAL(*list2.begin(), 2.2);
				BOOST_CHECK_EQUAL(list2.GetSize(), 1);
			}
			BOOST_AUTO_TEST_CASE(erase_of_a_single_element_in_end_does_not_make_list_of_invalid)
			{
				CStringList<double> list2;
				list2.Append(1.1);
				BOOST_REQUIRE_NO_THROW(list2.Erase(--list2.end()));
				list2.Append(2.2);
				BOOST_CHECK_EQUAL(list2.GetBackElement(), 2.2);
				BOOST_CHECK_EQUAL(*list2.begin(), 2.2);
				BOOST_CHECK_EQUAL(list2.GetSize(), 1);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(assignment_operator)
			BOOST_AUTO_TEST_CASE(can_assign_other_list_to_current_list)
			{
			CStringList<std::string> copy;
				copy = list;
				BOOST_CHECK_EQUAL(*copy.begin(), *list.begin());
				BOOST_CHECK_EQUAL(*--copy.end(), *--list.end());
				BOOST_CHECK_EQUAL(copy.GetSize(), list.GetSize());
			}
			BOOST_AUTO_TEST_CASE(can_assign_empty_list)
			{
				CStringList<std::string> copy;
				list = copy;
				BOOST_CHECK_THROW(*copy.begin(), std::runtime_error);
				BOOST_CHECK_THROW(*--copy.end(), std::runtime_error);
				BOOST_CHECK_EQUAL(copy.GetSize(), list.GetSize());
				BOOST_CHECK(copy.IsEmpty());
			}
			BOOST_AUTO_TEST_CASE(can_assign_list_with_single_element)
			{
				CStringList<std::string> copy;
				copy.Append("hi");
				list = copy;
				BOOST_CHECK_EQUAL(*copy.begin(), *list.begin());
				BOOST_CHECK_EQUAL(*--copy.end(), *--list.end());
				BOOST_CHECK_EQUAL(copy.GetSize(), list.GetSize());
			}
			BOOST_AUTO_TEST_CASE(can_assign_list_after_clean_it)
			{
				CStringList<std::string> copy;
				copy.Append("1");
				copy.Clear();
				list = copy;
				BOOST_CHECK_EQUAL(*copy.begin(), *list.begin());
				BOOST_CHECK_EQUAL(*--copy.end(), *--list.end());
				BOOST_CHECK_EQUAL(copy.GetSize(), list.GetSize());
				BOOST_CHECK_EQUAL(*--copy.rend(), *--list.rend());
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(my_list_construction_tests)
			struct MockObjWithDeletedBoolArgConstruct
			{
				MockObjWithDeletedBoolArgConstruct() = default;

				MockObjWithDeletedBoolArgConstruct(int num)
					: num(num)
				{
				};

				MockObjWithDeletedBoolArgConstruct(bool err)
				{
					throw std::out_of_range("Test Except.");
				}

				int num;
			};
			BOOST_FIXTURE_TEST_SUITE(tests_with_mock_obj_with_deleted_excepted_and_normal_construct, MockObjWithDeletedBoolArgConstruct)
				BOOST_AUTO_TEST_CASE(can_construct_my_list_with_deleted_default_constructor)
				{
					struct MockObjWithDefaultDeletedConstruct
					{
						MockObjWithDefaultDeletedConstruct() = delete;
					};
					BOOST_CHECK_NO_THROW(std::list<MockObjWithDefaultDeletedConstruct> lst);
					BOOST_CHECK_NO_THROW(CStringList<MockObjWithDefaultDeletedConstruct> lst);
				}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()