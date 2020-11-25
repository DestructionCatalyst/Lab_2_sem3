#pragma once

#include<string>
#include<stdexcept>
#include<sstream>

using std::string;
using std::stringstream;

class ParseException : public std::exception
{
public:
	ParseException():
		std::exception()
	{}

	ParseException(const char* message):
		std::exception(message)
	{}
};

//If expression is false, throws an exception
#define ENSURE(EXPRESSION, EXCEPTION) {if(!(EXPRESSION)) throw EXCEPTION;}

//If a string {str} doesn't contain char {c} on {index}, throws an exception
void EnsureChar(string str, char c, int index);

void EnsureFirst(string str, char c);

void EnsureLast(string str, char c);

int FindFirstAndEnsureContains(string str, char c);

template<class T1, class T2>
std::pair<T1, T2> ParsePair(string toParse)
{
	EnsureFirst(toParse, '(');
	EnsureLast(toParse, ')');

	size_t semicolonIndex = FindFirstAndEnsureContains(toParse, ';');

	T1 first;
	T2 second;

	stringstream stream1{ toParse.substr(1, semicolonIndex - 1) };
	stringstream stream2{ toParse.substr(semicolonIndex + 1, string::npos) };

	try {
		stream1 >> first;
		stream2 >> second;
	}
	catch (...)
	{
		throw ParseException();
	}

	return std::make_pair(first, second);
}