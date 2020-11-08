#pragma once
#include "INumberGenerator.h"
class ConstantNumberGenerator :
	public INumberGenerator
{
private:
	int numberToReturn;
public:
	ConstantNumberGenerator(int number);
	int NextItem() override;
};

