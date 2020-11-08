#pragma once
#include <functional>
#include <iostream>

#include "LinkedList.h"
#include "Sequence.h"
#include "ListIterator.h"
#include "SequenceIterator.h"
#include "ItemGenerator.h"

#define min(num1, num2) ((num1<num2)?num1:num2)

namespace sequences {
	template <class T> class ListSequence : public Sequence<T> {
	public:
		typedef sequences::iterators::ListIterator<T> const_iterator;
		typedef sequences::iterators::MutableListIterator<T> iterator;
	private:
		LinkedList<T>* list;
	public:
		//Creation
		ListSequence()
			:Sequence<T>()
		{
			list = new LinkedList<T>();
		}
		ListSequence(T* items, int count)
			:Sequence<T>()
		{
			list = new LinkedList<T>(items, count);
		}
		ListSequence(ListSequence<T>& newList)
			:Sequence<T>()
		{
			list = new LinkedList<T>(*(newList.list));
		}
		ListSequence(const std::initializer_list<T>& initList):
			ListSequence<T>()
		{
			auto initIter = initList.begin();

			for (; initIter != initList.end(); ++initIter) {

				Append(*initIter);
			}

		}
		ListSequence(ItemGenerator<T>* gen, int length):
			ListSequence<T>()
		{
			for (int i = 0; i < length; i++)
				list->Append(gen->NextItem());
		}
		//Decomposition
		T GetFirst() const override
		{
			return list->GetFirst();
		}
		T GetLast() const override
		{
			return list->GetLast();
		}
		T Get(int index) const override
		{
			return list->Get(index);
		}
		Sequence<T>* GetSubsequence(int startIndex, int endIndex) override
		{
			return new ListSequence<T>(list->GetSubList(startIndex, endIndex));
		}
		int GetLength() const override
		{
			return list->GetLength();
		}
		//Operations
		void Append(T item) override
		{
			list->Append(item);
		}
		void Prepend(T item) override
		{
			list->Prepend(item);
		}
		void InsertAt(T item, int index) override
		{
			list->InsertAt(item, index);
		}
		void Set(T item, int index) override
		{
			itemIterator(index).SetContent(item);
		}
		//Creates a copy and concatenates {list} to it 
		Sequence<T>* Concat(Sequence<T>* list) override
		{
			ListSequence<T>* bigList = new ListSequence(*this);

			for (int i = 0; i < list->GetLength(); i++) {
				bigList->Append(list->Get(i));
			}
			return bigList;
		}
		void Swap(int item1, int item2) override
		{
			list->Swap(item1, item2);
		}
	public:
		void Print() const override
		{
			const_iterator iter = dcast(begin());
			for (; iter != dcast(end()); ++iter)
			{
				std::cout << *iter << " ";
			}
			std::cout << std::endl;
		}
		Sequence<T>* Map(std::function<T(T)> f) const override
		{
			ListSequence<T>* newList = new ListSequence<T>();

			const_iterator itr = dcast(begin());

			for (; itr != dcast(end()); ++itr)
			{
				newList->Append(f(*itr));
			}

			return newList;
		}
		Sequence<T>* Where(std::function<bool(T)> f) const override
		{
			ListSequence<T>* newList = new ListSequence<T>();
			T cur;

			const_iterator itr = dcast(begin());

			for (; itr != dcast(end()); ++itr)
			{
				cur = *itr;
				if (f(cur))
					newList->Append(cur);
			}
			
			return newList;
		}
		T Reduce(std::function<T(T, T)> f, T c) const override
		{
			T funcResult = c;

			const_iterator itr = dcast(begin());

			for (; itr != dcast(end()); ++itr)
			{
				funcResult = f(*itr, funcResult);
			}
			
			return funcResult;
		}

		~ListSequence()
		{
			delete(list);
		}
	private:
		const_iterator dcast(Sequence<T>::const_iterator* iter) const
		{
			return *dynamic_cast<const_iterator*>(iter);
		}
	public:
		Sequence<T>::const_iterator* begin() const override
		{
			return list->begin_();
		}
		Sequence<T>::const_iterator* end() const override
		{
			return list->end_();
		}
		Sequence<T>::const_iterator* itemIterator(int index) const override
		{
			return list->itemIterator_(index);
		}
	public:
		iterator begin() 
		{
			return list->begin();
		}
		iterator end() 
		{
			return list->end();
		}
		iterator itemIterator(int index) 
		{
			return list->itemIterator(index);
		}

	private:
		ListSequence(LinkedList<T>* listToWrap)
			:Sequence<T>()
		{
			list = listToWrap;
		}
	};
}
