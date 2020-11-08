#pragma once


template <class T> class ItemGenerator
{
public:
	ItemGenerator()
	{}

	virtual T NextItem() = 0;
};