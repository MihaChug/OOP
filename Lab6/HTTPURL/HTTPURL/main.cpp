// HTTPURL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "HttpUrl.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <boost/lexical_cast.hpp>


std::vector<std::string> ParseArgs(std::string const &inputStr)
{
	std::string arg;
	std::istringstream strm(inputStr);
	std::vector<std::string> args;

	while (strm >> arg)
	{
		args.push_back(arg);
	}

	return args;
}

std::unique_ptr<CHttpUrl> MakePtrToUrl(std::vector<std::string> &args)
{
	std::unique_ptr<CHttpUrl> url;

	switch (args.size())
	{
	case (1) :
		url = std::make_unique<CHttpUrl>(args[0]);
		break;
	case (2) :
		url = std::make_unique<CHttpUrl>(args[0], args[1]);
		break;
	case (3) :
		url = std::make_unique<CHttpUrl>(args[0], args[1], url->ToProtocolType(args[2]));
		break;
	case (4) :
		url = std::make_unique<CHttpUrl>(args[0], args[1], url->ToProtocolType(args[2]), boost::lexical_cast<unsigned short>(args[3]));
		break;
	}

	return url;
}

void PrintURLContains(std::unique_ptr<CHttpUrl> const &url)
{
	std::cout << "=================" << std::endl;
	std::cout << "Protocol: " << url->ToStringProtocol() << std::endl;
	std::cout << "Domain name: " << url->GetDomain() << std::endl;
	std::cout << "Document: " << url->GetDocument() << std::endl;
	std::cout << "Port: " << url->GetPort() << std::endl;
	std::cout << "URL: " << url->GetUrl() << std::endl;
	std::cout << "=================" << std::endl << std::endl;
}

void InteractWithUser()
{
	std::string inputStr;
	while (std::getline(std::cin, inputStr))
	{
		try
		{
			if (inputStr.empty())
			{
				throw std::invalid_argument("Input string is empty.");
			}

			auto args = ParseArgs(inputStr);
			auto url = MakePtrToUrl(args);

			if (!url)
			{
				throw std::invalid_argument("Invalid arguments count.");
			}

			PrintURLContains(url);
		}
		catch (std::invalid_argument const &err)
		{
			std::cout << err.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Unknow error type." << std::endl;
		}
	}
}

int main()
{
	InteractWithUser();
	return 0;
}