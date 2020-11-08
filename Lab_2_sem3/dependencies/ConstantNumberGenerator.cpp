#include "ConstantNumberGenerator.h"

ConstantNumberGenerator::ConstantNumberGenerator(int number):
	INumberGenerator(), numberToReturn(number)
{}

int ConstantNumberGenerator::NextItem()
{
	return numberToReturn;
}