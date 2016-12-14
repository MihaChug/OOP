// ParseURL.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "ParseURL.h"
#include <boost/algorithm/string.hpp>

using namespace std;

void SetProtocolType(string const &protocolStr, Protocol &protocol)
{
	if (protocolStr == "http")
	{
		protocol = Protocol::HTTP;
	}
	else if (protocolStr == "https")
	{
		protocol = Protocol::HTTPS;
	}
	else if (protocolStr == "ftp")
	{
		protocol = Protocol::FTP;
	}
}

bool ParseURL(string const &url, Protocol &protocol, int &port, std::string &host, std::string &document)
{
	boost::regex ex("(http|https|ftp)://([^/ :]+):?([^/ ]*)/([^ ]*)");
	boost::cmatch what;

	auto checkingUrl = url;
	boost::algorithm::to_lower(checkingUrl);

	if (regex_match(checkingUrl.c_str(), what, ex))
	{
		checkingUrl = url;
		auto protocolStr = string(what[1].first, what[1].second);
		boost::algorithm::to_lower(protocolStr);
		SetProtocolType(protocolStr, protocol);

		host = string(what[2].first, what[2].second);

		string portStr = string(what[3].first, what[3].second);
		port = atoi(portStr.c_str());
		if (port == 0)
		{
			port = static_cast<int>(protocol);
		}

		document = string(what[4].first, what[4].second);

		return true;
	}

	return false;
}

