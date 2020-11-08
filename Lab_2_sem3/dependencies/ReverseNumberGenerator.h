#pragma once
#include "INumberGenerator.h"
class ReverseNumberGenerator :
	public INumberGenerator
{
private:
	int numberToReturn;
public:
	ReverseNumberGenerator(int startNumber);
	int NextItem() override;
};

