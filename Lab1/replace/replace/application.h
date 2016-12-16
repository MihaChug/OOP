#pragma once
#include "replace.h"

bool IsCountArgumentsCorrect(int const &argc);
bool CopyFileWithStringReplacing(char *nameInputFile, char *nameOutputFile, std::string const &searchString, std::string replaceString);