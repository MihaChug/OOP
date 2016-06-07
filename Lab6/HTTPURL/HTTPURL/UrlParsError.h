#pragma once
#include <stdexcept>
#include <string>

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443
};

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(std::string const &msg = std::string());
};