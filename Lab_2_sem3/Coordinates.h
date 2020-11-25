#pragma once
#include <utility>
#include <stdexcept>
#include <fstream>
#include <string>

#include "ParseFunctions.h"
#include "PairInOut.h"

using std::string;

#define PRIME1 31
#define PRIME2 47


class Coordinates {
private:
	std::pair<int, int> coords;
		
public:
	Coordinates()
	{
		coords = std::make_pair(0, 0);
	}
	Coordinates(int row, int col)
	{
		if (row >= 0 && col >= 0)
			coords = std::make_pair(row, col);
		else
			throw std::invalid_argument("Index of coordinates can't be negative!");
	}
public:
	int GetRow()
	{
		return coords.first;
	}
	int GetColumn()
	{
		return coords.second;
	}
	friend bool operator ==(Coordinates o1, Coordinates o2);
	friend bool operator !=(Coordinates o1, Coordinates o2);

	friend std::ostream& operator<<(std::ostream& out, const Coordinates& c);
	friend std::istream& operator>>(std::istream& in, Coordinates& c);
		
};
int coordinatesHash(Coordinates coord, int table_size);


	


