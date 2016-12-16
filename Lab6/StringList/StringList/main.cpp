#include "stdafx.h"
#include <list>
#include <iostream>
#include <string>
#include "StringList.h"


using namespace std;

int main()
{
	//{
	//	unique_ptr<string> ptr1 = make_unique<string>("zzz");
	//	string * ptr2 = new string("ASD");

	//	ptr1.reset(ptr2);
	//	cout << *ptr1 <<" " << *ptr2 << " " << (ptr1.get() == ptr2)<< endl;
	//}


	//{
	//	list<string> lstt = {"2"};
	//	cout << lstt.back() << endl;
	//	std::list<string> lst = { "1222" };
	//	auto end1 = lst.end();
	//	lst.push_back("123123123");	
	//	cout << (lst.end() == end1) << endl;

	//	auto end = lst.end();
	//	cout << *(--lst.end()) << endl;

	//	lstt.emplace(lstt.begin(), "zzz");
	//	cout << lstt.front() << endl;
	//}

	//{
	//	//CMyList lst;
	//	//for (size_t i = 0; i < 99999; ++i)
	//	//{
	//	//	lst.Append("asd");
	//	//}
	//	//lst.Clear();
	//}
	//{
	//	CMyList<std::string> list;
	//	list.Append("123");
	////	cout << *(list.end()) << endl;
	//	cout << *(list.begin()) << endl;
	//}


	{
		cout << "123" << endl;
		CStringList<std::string> lst_;
//		cout << *lst_.begin() << endl;
		lst_.Append("1");
		lst_.Append("2");
		lst_.Append("3");
		lst_.Append("4");
		lst_.Append("5");
		for (auto it = lst_.begin(); it != lst_.end(); ++it)
		{
			cout << *it << endl;
		}
		cout << "123" << endl;

		CStringList<std::string> lst2;
		lst2 = lst_;
	}
	{
		CStringList<std::string> lst_;
		lst_.AddToFront("1");
		lst_.AddToFront("2");
		lst_.AddToFront("3");
		lst_.AddToFront("4");
		lst_.AddToFront("5");
		for (auto it = lst_.begin(); it != lst_.end(); ++it)
		{
			cout << *it << endl;
		}
		for (auto it = lst_.rbegin(); it != lst_.rend(); ++it)
		{
			cout << *it << " Range-based-for" << endl;
		}
	}

	{
		CStringList<double> lst;
		auto end = lst.begin();
		auto end1 = lst.end();
	}

	//	auto bb = ++lst_.begin();
	//	lst_.Insert(bb, "WOW22");

	//	cout << lst_.GetFrontElement() << endl;

	//	auto end = lst_.end();
	//	lst_.Append("aaa");
		
		//cout << endl << (end == lst_.end()) << endl;

	CStringList<std::string> lst1;
	lst1.Append("1");
	lst1.Append("2");
	lst1.Append("3");
	
	CStringList<std::string> lst2;
	lst2 = lst1;


	struct MockObjWithDefaultExceptedConstruct
	{
		MockObjWithDefaultExceptedConstruct()
		{
			throw std::runtime_error("Test except");
		}
		MockObjWithDefaultExceptedConstruct(int num)
			: num(num)
		{
		};
		int num;
	};
	CStringList<MockObjWithDefaultExceptedConstruct> lst;

	struct Node
	{
		Node* m_node;
		std::function<void()> a = [this]() {m_node = m_node->m_node; };
	};

	return 0;
}

