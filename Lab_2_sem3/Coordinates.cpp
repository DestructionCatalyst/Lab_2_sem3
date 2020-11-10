#include "Coordinates.h"

namespace matrix {
	int CoordinatesHash(Coordinates coord, int table_size)
	{
		int key = table_size - 1;
		int hash_result = 0;

		hash_result = (key * hash_result + coord.GetRow()) % table_size;
		hash_result = (key * hash_result + coord.GetColumn()) % table_size;
		hash_result = (hash_result * 2 + 1) % table_size;

		return hash_result;
	}
}