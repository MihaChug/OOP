#pragma once
#include <sstream>

struct SportsMan
{
	SportsMan() = default;
	SportsMan(std::string const &firstName, std::string const &middleName
		, std::string const &lastName, double height, double weight)
		: firstName(firstName)
		, middleName(middleName)
		, lastName(lastName)
		, height(height)
		, weight(weight)
	{
	}
	std::string firstName;
	std::string middleName;
	std::string lastName;
	double height;
	double weight;
};

std::istream &operator >>(std::istream &strm, SportsMan & sportsman)
{
	strm >> sportsman.firstName
		 >> sportsman.middleName
		 >> sportsman.lastName
		 >> sportsman.height
		 >> sportsman.weight;

	return strm;
}