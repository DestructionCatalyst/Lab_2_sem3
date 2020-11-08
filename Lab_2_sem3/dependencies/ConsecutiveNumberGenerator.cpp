#include "ConsecutiveNumberGenerator.h"


ConsecutiveNumberGenerator::ConsecutiveNumberGenerator(int startNumber) :
	INumberGenerator(), numberToReturn(startNumber)
{}

int ConsecutiveNumberGenerator::NextItem()
{
	return numberToReturn++;
}
