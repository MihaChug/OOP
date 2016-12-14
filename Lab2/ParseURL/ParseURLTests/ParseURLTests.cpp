// ParseURLTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../ParseURL/ParseURL.h"

BOOST_AUTO_TEST_SUITE(ParseURLTests)

BOOST_AUTO_TEST_CASE(ParseURL_try1)
{
	int port;
	Protocol protocol;
	std::string host;
	std::string document;
	BOOST_CHECK_EQUAL(ParseURL("https://github.com/oMystique/OOP/", protocol, port, host, document), true);
	BOOST_CHECK_EQUAL(port, 443);
	BOOST_CHECK_EQUAL(document, "oMystique/OOP/");
};

BOOST_AUTO_TEST_CASE(ParseURL_try2)
{
	int port;
	Protocol protocol;
	std::string host;
	std::string document;
	BOOST_CHECK_EQUAL(ParseURL("https:/github.com/oMystique/OOP/", protocol, port, host, document), false);
};

BOOST_AUTO_TEST_CASE(ParseURL_try3)
{
	int port;
	Protocol protocol;
	std::string host;
	std::string document;
	BOOST_CHECK_EQUAL(ParseURL("HTTP://www.mysite.com/docs/document1.html?page=30&lang=en#title", protocol, port, host, document), true);
	BOOST_CHECK_EQUAL(port, 80);
	BOOST_CHECK_EQUAL(document, "docs/document1.html?page=30&lang=en#title");
};

BOOST_AUTO_TEST_CASE(ParseURL_try4)
{
	int port;
	Protocol protocol;
	std::string host;
	std::string document;
	BOOST_CHECK_EQUAL(ParseURL("ftp://files.vk.com:2007/", protocol, port, host, document), true);
	BOOST_CHECK_EQUAL(port, 2007);
	BOOST_CHECK_EQUAL(document, "");
};

BOOST_AUTO_TEST_SUITE_END()

