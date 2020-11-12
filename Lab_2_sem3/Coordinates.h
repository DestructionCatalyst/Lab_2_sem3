#pragma once
#include <utility>

#define PRIME1 31
#define PRIME2 47


namespace matrix {
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
			coords = std::make_pair(row, col);
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
		
	};
	int coordinatesHash(Coordinates coord, int table_size);
	bool operator ==(Coordinates o1, Coordinates o2);
	bool operator !=(Coordinates o1, Coordinates o2);
}

