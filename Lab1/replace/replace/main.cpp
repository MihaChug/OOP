#include "application.h"

int main(int argc, char *argv[])
{
	if (IsCountArgumentsCorrect(argc))
	{
		return !CopyFileWithStringReplacing(argv[1], argv[2], argv[3], argv[4]);
	}
	return 1;
}