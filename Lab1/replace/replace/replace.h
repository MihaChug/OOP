#pragma once
#include <string>
#include <iostream>
#include <fstream>

void StringReplacing(std::string const &searchString, std::string const &replaceString,
	std::ifstream &inputFile, std::ofstream &outputFile);
bool IsSearchStringNotEmpty(std::string const &searchString);