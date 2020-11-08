#pragma once
#include "INumberGenerator.h"
class ConsecutiveNumberGenerator :
	public INumberGenerator
{
private:
	int numberToReturn;
public:
	ConsecutiveNumberGenerator(int startNumber);
	int NextItem() override;
};

