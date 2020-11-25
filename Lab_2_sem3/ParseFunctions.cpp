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
	size_t index = string::npos;

	int depth = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ')')
			depth++;
		else if (str[i] == '(')
			depth--;
		else if (depth == 0)
			if (str[i] == c) {
				index = i;
				break;
			}
	}

	ENSURE(index != string::npos, ParseException());

	return index;
}


