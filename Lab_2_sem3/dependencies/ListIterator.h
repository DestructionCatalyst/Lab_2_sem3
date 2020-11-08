#pragma once
#include "Node.h"
#include "SequenceIterator.h"

namespace sequences
{
	namespace iterators
	{

		template<class T> class ListIterator: public SequenceIterator<T>{
		protected:
			Node<T>* ptr;
		public:
			ListIterator(Node<T>* start) :
				SequenceIterator<T>(), ptr(start)
			{}

			ListIterator(const ListIterator<T>& iter):
				SequenceIterator<T>(), ptr(iter.ptr)
			{}

		public:
			ListIterator& operator++() override
			{
				if (ptr == nullptr)
					throw std::out_of_range("Iterator is out of bounds!");
				else
					ptr = ptr->Next();
				return *this;
			}
			T operator*() const override
			{
				return ptr->GetContent();
			}
			bool operator== (const SequenceIterator<T>& o) const override
			{
				try {
					const ListIterator<T>& list_o = dynamic_cast<const ListIterator<T>&>(o);
					return ptr == list_o.ptr;
				}
				catch (std::bad_cast e) {
					return false;
				}
			}
			bool operator!=(const SequenceIterator<T>& o) const override
			{
				return !(*this == o);
			}
			/*
			bool operator== (const ListIterator<T>& o) const 
			{
				return ptr == o.ptr;
			}
			bool operator!=(const ListIterator<T>& o) const 
			{
				return !(*this == o);
			}
			*/
			
		};
	}
}