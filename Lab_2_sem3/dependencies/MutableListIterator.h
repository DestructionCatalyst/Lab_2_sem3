#pragma once

#include "MutableSequenceIterator.h"
#include "ListIterator.h"
#include "LinkedList.h"
#include "Node.h"

namespace sequences
{
	namespace iterators
	{

		template<class T> class MutableListIterator : public ListIterator<T>, public MutableSequenceIterator<T>
		{
			
		public:
			MutableListIterator(Node<T>* start) :
				MutableSequenceIterator<T>(), ListIterator<T>(start)
			{}

			MutableListIterator(const MutableListIterator<T>& iter) :
				ListIterator<T>(iter)
			{}
		public:
			void SetContent(T content) override
			{
				this->ptr->SetContent(content);
			}
			void SetNext(Node<T>* next)
			{
				this->ptr->SetNext(next);
			}
			Node<T>* GetNextPointer()
			{
				return this->ptr->Next();
			}
			operator Node<T>* () const
			{
				return this->ptr;
			}

		};

	}
}