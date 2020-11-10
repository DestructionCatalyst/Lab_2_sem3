#pragma once
#include <utility>

namespace matrix {
	class Coordinates {
	private:
		std::pair<int, int> coords;
		
	public:
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
		
	};
	int CoordinatesHash(Coordinates coord, int table_size);
}

