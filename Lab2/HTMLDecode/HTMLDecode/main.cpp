#include "stdafx.h"
#include <iostream>
#include "HTMLDecode.h"
#include <boost/utility/string_ref.hpp>

using namespace std;

string ReadingFromStream()
{
	string inputString;
	getline(cin, inputString);
	return inputString;
}

int _tmain()
{
	cout << "Input html string for decoding: " << endl;
	string inputString(ReadingFromStream());
	string outputString = HTMLDecode(inputString);
	cout << "Output decoded string: " << endl;
	cout << outputString << endl;
	return 0;
}
