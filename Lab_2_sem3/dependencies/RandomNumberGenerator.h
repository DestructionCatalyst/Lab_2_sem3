#pragma once

#include <ctime>
#include <random>

#include "INumberGenerator.h"

class RandomNumberGenerator :
	public INumberGenerator
{
private:
	//int seed;
public:
	RandomNumberGenerator();
	RandomNumberGenerator(int seed);
	int NextItem() override;
};

