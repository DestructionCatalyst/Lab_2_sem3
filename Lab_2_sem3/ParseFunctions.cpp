#include "ParseFunctions.h"

void EnsureChar(string str, char c, int index)
{
	ENSURE(str[index] == c, ParseException())
}

void EnsureFirst(string str, char c)
{
	EnsureChar(str, c, 0);
}

void EnsureLast(string str, char c)
{
	EnsureChar(str, c, str.size() - 1);;
}

int FindFirstAndEnsureContains(string str, char c)
{
	size_t index = str.find_first_of(c);

	ENSURE(index != string::npos, ParseException());

	return index;
}


