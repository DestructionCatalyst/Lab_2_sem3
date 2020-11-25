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

