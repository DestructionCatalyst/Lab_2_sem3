#pragma once

#include <stdexcept>

#include "SequenceIterator.h"
#include "ArraySequence.h"

namespace sequences
{
	namespace iterators
	{
		template<class T> class ArrayIterator: public SequenceIterator<T>{
		protected:
			int index;
			const Sequence<T>* arr;//Cant be ArraySequence. Why?
		public:
			ArrayIterator(const Sequence<T>* myArray):
				SequenceIterator<T>(), index(0)
			{
				arr = myArray;
			}
			ArrayIterator(const Sequence<T>* myArray, int startIndex):
				SequenceIterator<T>(), index(startIndex)
			{
				arr = myArray;
			}
		public:
			SequenceIterator<T>& operator++ () override
			{
				++index;
				return *this;
			}
			T operator* () const override
			{
				if(index < arr->GetLength())
					return arr->Get(index);
				throw std::out_of_range("Iterator is out of bounds!");
			}
			bool operator== (const SequenceIterator<T>& o) const override
			{
				try {
					const ArrayIterator<T>& array_o = dynamic_cast<const ArrayIterator<T>&>(o);
					return (index == array_o.index) && (arr == array_o.arr);
				}
				catch (std::bad_cast e) {
					return false;
				}
			}
			bool operator!=(const SequenceIterator<T>& o) const override
			{
				return !(*this == o);
			}
		};
	}
}