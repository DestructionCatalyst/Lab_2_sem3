#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator() :
	INumberGenerator()
{
	srand(time(nullptr));
}

RandomNumberGenerator::RandomNumberGenerator(int seed) :
	INumberGenerator()//, seed(seed)
{
	srand(seed);
}

int RandomNumberGenerator::NextItem()
{
	return rand();
}