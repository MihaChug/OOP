#include "stdafx.h"
#include "UrlParsError.h"

CUrlParsingError::CUrlParsingError(std::string const & msg): std::invalid_argument(msg)
{
};