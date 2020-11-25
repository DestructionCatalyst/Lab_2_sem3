#include "Coordinates.h"

int coordinatesHash(Coordinates coord, int table_size)
{
	return (PRIME1 * coord.GetRow() + PRIME2 * coord.GetColumn()) % table_size;
}
bool operator==(Coordinates o1, Coordinates o2)
{
	return o1.GetRow() == o2.GetRow() && o1.GetColumn() == o2.GetColumn();
}
bool operator!=(Coordinates o1, Coordinates o2)
{
	return !(o1 == o2);
}
std::ostream& operator<<(std::ostream& out, Coordinates& c)
{
	return out << c.coords;
}
	
std::istream& operator>>(std::istream& in, Coordinates& c)
{
	in >> c.coords;

	return in;
}
	


