#pragma once
#include <string>
#include <boost/utility/string_ref.hpp>

std::string HTMLDecode(boost::string_ref const &htmlString);