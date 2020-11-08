#pragma once

#include <functional>

#include "SequenceIterator.h"

namespace sequences {
	template <class T> class Sequence {
	public:

		typedef sequences::iterators::SequenceIterator<T> const_iterator;

		Sequence() {
		};

		//Decomposition

		virtual T GetFirst() const = 0;
		virtual T GetLast() const = 0;
		virtual T Get(int index) const = 0;
		virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
		virtual int GetLength() const = 0;

		//Operations
		//Constant time for every type
		virtual void Append(T item) = 0;


		virtual void Prepend(T item) = 0;
		virtual void InsertAt(T item, int index) = 0;
		
		virtual void Set(T item, int index) = 0;

		virtual Sequence<T>* Concat(Sequence<T>* list) = 0;

		virtual Sequence<T>* Map(std::function<T(T)> f) const = 0;
		virtual Sequence<T>* Where(std::function<bool(T)> f) const = 0;
		virtual T Reduce(std::function<T(T, T)> f, T) const = 0;

		virtual const_iterator* begin() const = 0;
		virtual const_iterator* end() const = 0;
		virtual const_iterator* itemIterator(int index) const = 0;

		virtual void Swap(int item1, int item2) = 0;

		virtual void Print() const = 0;

		virtual ~Sequence() {};
	};
}