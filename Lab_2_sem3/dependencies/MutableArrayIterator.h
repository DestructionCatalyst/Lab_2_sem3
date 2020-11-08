#pragma once

#include "MutableSequenceIterator.h"
#include "ArrayIterator.h"
#include "ArraySequence.h"

namespace sequences
{
	namespace iterators
	{
		//UNUSED
		template<class T> class MutableArrayIterator : public ArrayIterator<T>, public MutableSequenceIterator<T>
		{

		public:
			MutableArrayIterator(const Sequence<T>* myArray) :
				ArrayIterator<T>(myArray)
			{}
			MutableArrayIterator(const Sequence<T>* myArray, int startIndex) :
				ArrayIterator<T>(myArray, startIndex)
			{}
		public:
			void SetContent(T content) override
			{
				this->arr->Set(content, this->index);
			}

		};

	}
}