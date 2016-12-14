// HTMLDecode.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <map>
#include "HTMLDecode.h"

using namespace std;

const char ENCODED_CHAR_BEGINNING = '&';

string HTMLDecode(boost::string_ref const &htmlString)
{
	map<string, string> arrayOfCharactersToReplaced = 
	{ 
		{"&quot;", "\"" },
		{"&apos;", "'"},
		{"&lt;", "<"},
		{"&gt;", ">"},
		{"&amp;", "&"}
	};
	string returnString;
	bool isReplaced = false;
	for (unsigned i = 0; i < htmlString.size(); i++)
	{
		isReplaced = false;
		if (htmlString[i] == ENCODED_CHAR_BEGINNING)
		{
			for (auto it = arrayOfCharactersToReplaced.begin(); it != arrayOfCharactersToReplaced.end(); it++)
			{
				if (htmlString.substr(i, it->first.size()) == it->first)
				{
					returnString.append(it->second);
					i += it->first.size() - 1;
					isReplaced = true;
					break;
				}
			}
		}
		if (!isReplaced)
		{
			returnString += htmlString[i];
		}
	}
	return returnString;
}

