#pragma once

#include <functional>
#include <iostream>

#include "DynamicArray.h"
#include "Sequence.h"
#include "ArrayIterator.h"
#include "MutableArrayIterator.h"
#include "ItemGenerator.h"

#define DEFAULT_SIZE 8
#define min(num1, num2) ((num1<num2)?num1:num2)


namespace sequences {
	template <class T> class ArraySequence : public Sequence<T> {
	public:
		typedef sequences::iterators::ArrayIterator<T> const_iterator;
		typedef sequences::iterators::MutableArrayIterator<T> iterator;
	private:
		DynamicArray<T>* arr;
		int curSize;
	public:

		//Creation
		ArraySequence()
			:Sequence<T>()
		{
			arr = new DynamicArray<T>(DEFAULT_SIZE);
			curSize = 0;
		}
		ArraySequence(int size)
			:Sequence<T>()
		{
			arr = new DynamicArray<T>(size + 8);
			curSize = 0;
		}
		ArraySequence(T* items, int count)
			:Sequence<T>()
		{
			arr = new DynamicArray<T>(items, count);
			curSize = count;
		}
		ArraySequence(const ArraySequence<T>& array)
			:Sequence<T>(), curSize(array.curSize)
		{
			arr = new DynamicArray<T>(*(array.arr));
		}
		ArraySequence(const std::initializer_list<T>& initList)
			:Sequence<T>(), curSize(0)
		{
			auto initIter = initList.begin();
			arr = new DynamicArray<T>(initList.size());

			for (; initIter != initList.end(); ++initIter ) {
				
				Append(*initIter);
			}

		}
		ArraySequence(ItemGenerator<T>* gen, int length):
			Sequence<T>(), curSize(length)
		{
			arr = new DynamicArray<T>(length);

			for (int i = 0; i < length; i++)
			{
				Set(gen->NextItem(), i);
			}
		}

		//Decomposition

		T GetFirst() const override
		{
			return arr->Get(0);
		} 
		T GetLast() const override
		{
			return arr->Get(curSize - 1);
		}
		T Get(int index) const override
		{
			if (index < curSize)
				return arr->Get(index);
			else throw std::out_of_range("Sequence index is out of bounds");
		}
		//Copies the part of the sequence
		Sequence<T>* GetSubsequence(int startIndex, int endIndex) override
		{
			if ((startIndex <= endIndex) && (startIndex >= 0) && (endIndex < curSize)) {
				ArraySequence<T>* sub = new ArraySequence();
				for (int i = startIndex; i <= endIndex; i++) {
					sub->Append(T(Get(i)));
				}
				return sub;
			}
			else
				throw std::out_of_range("Sequence index is out of bounds");
		}
		int GetLength() const override 
		{
			return curSize;
		}
		//Operations

		void Append(T item) override
		{
			ExpandIfNeeded();
			arr->Set(item, curSize);
			curSize++;
		}
		void Prepend(T item) override
		{
			ExpandIfNeeded();
			for (int i = curSize; i > 0; i--)
				arr->Set(arr->Get(i - 1), i);
			arr->Set(item, 0);
			curSize++;
		}
		void InsertAt(T item, int index) override
		{
			if (index == 0)
				Prepend(item);
			else if (index == curSize)
				Append(item);
			else if ((index > 0) && (index < curSize)) {
				ExpandIfNeeded();

				for (int i = curSize; i >= index; i--)
					arr->Set(arr->Get(i - 1), i);
				arr->Set(item, index);
				curSize++;
			}
			else
				throw std::out_of_range("Sequence index is out of bounds");
		}
		void Set(T item, int index) override
		{
			arr->Set(item, index);
		}

		void Swap(int item1, int item2) override
		{
			T tmp = Get(item1);
			Set(Get(item2), item1);
			Set(tmp, item2);
		}
		
		//Creates a copy and concatenates {list} to it 
		Sequence<T>* Concat(Sequence<T>* list) override
		{
			ArraySequence<T>* bigArr = new ArraySequence(*this);
			for (int i = 0; i < list->GetLength(); i++) {
				bigArr->Append(T(list->Get(i)));
			}
			return bigArr;
		}
		//Returns transformed copy
		Sequence<T>* Map(std::function<T(T)> f) const override 
		{
			ArraySequence<T>* newArr = new ArraySequence<T>();

			const_iterator iter = dcast(begin());

			for (; iter != dcast(end()); ++iter)
				newArr->Append(f(*iter));
			
			return newArr;
		}
		Sequence<T>* Where(std::function<bool(T)> f) const override 
		{
			ArraySequence<T>* newList = new ArraySequence<T>();

			const_iterator iter = dcast(begin());

			for (; iter != dcast(end()); ++iter)
				if (f(*iter))
					newList->Append(*iter);

			return newList;
		}
		T Reduce(std::function<T(T, T)> f, T c) const override
		{
			T funcResult = c;

			const_iterator iter = dcast(begin());

			for (; iter != dcast(end()); ++iter)
				funcResult = f(*iter, funcResult);
			
			return funcResult;
		}
	public:
		void Clear()
		{
			curSize = 0;
		}
			/*
	public:
		void Swap(int firstIndex, int secondIndex) override
		{
			T temp = Get(firstIndex);
			Set(Get(secondIndex), firstIndex);
			Set(temp, secondIndex);
		}
		*/
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
	private:
		const_iterator dcast(Sequence<T>::const_iterator* iter) const
		{
			return *dynamic_cast<const_iterator*>(iter);
		}
	public:
		Sequence<T>::const_iterator* begin() const override
		{
			
			return new const_iterator(this);
		}
		Sequence<T>::const_iterator* end() const override
		{
			return new const_iterator(this, curSize);
		}
		Sequence<T>::const_iterator* itemIterator(int index) const override
		{
			return new const_iterator(this, index);
		}
		~ArraySequence()
		{
			delete(arr);
		}
	private:
		void ExpandIfNeeded(int multiplier = 2)
		{
			if (curSize >= arr->GetCapacity() - 1) {
				arr->Resize(arr->GetCapacity() * multiplier);
			}
		}
	};
}