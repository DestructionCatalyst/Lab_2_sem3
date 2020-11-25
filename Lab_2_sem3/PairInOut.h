#pragma once

#include <utility>
#include <iostream>

#include "ParseFunctions.h"
#include"Coordinates.h"

using std::pair;
using std::string;
using std::istream;
using std::ostream;

template<class T1, class T2>
istream& operator>> (istream& in, pair<T1, T2>& inPair)
{
	string toParse;

	in >> toParse;

	EnsureFirst(toParse, '(');
	EnsureLast(toParse, ')');

	size_t semicolonIndex = FindFirstAndEnsureContains(toParse, ';');

	stringstream stream1{ toParse.substr(1, semicolonIndex - 1) };
	stringstream stream2{ toParse.substr(semicolonIndex + 1, string::npos) };

	try {
		stream1 >> inPair.first;
		stream2 >> inPair.second;
	}
	catch (...)
	{
		throw ParseException();
	}

	return in;
}

template<class T1, class T2>
ostream& operator<< (ostream& out, const std::pair<T1, T2> outPair)
{
	out << "(" << outPair.first << ";" << outPair.second << ")";

	return out;
}
