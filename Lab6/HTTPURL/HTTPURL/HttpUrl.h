#pragma once
#include "UrlParsError.h"
#include <tuple>
#include <boost/utility/string_ref.hpp>

class CHttpUrl
{
	using UrlComponents = std::tuple<Protocol, std::string, unsigned short, std::string>;

public:
	CHttpUrl(std::string const &url);
	CHttpUrl
	(
		std::string const &domain,
		std::string const &document,
		Protocol protocol = Protocol::HTTP,
		unsigned short port = 80
	);
	
	std::string GetUrl()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;

	std::string ToStringProtocol()const;
	static Protocol ToProtocolType(std::string const &scheme);

private:
	static std::string const& ValidateDomainName(std::string const &domain);
	static std::string ValidateDocument(std::string const &document);
	static std::string ParseDomain(boost::string_ref &str);
	static std::string ParseProtocol(boost::string_ref &str);
	static std::string ParsePort(boost::string_ref &str);
	static UrlComponents ParseUrl(std::string const &url);

private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};