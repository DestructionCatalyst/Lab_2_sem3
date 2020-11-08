#pragma once

#include <functional>

#include "dependencies/DynamicArray.h"
#include "dependencies/LinkedList.h"
using namespace sequences;

namespace dictionary {
	template<class T>
	class HashTable {
	public:
		//Hash function takes an item and a table size, and returns an index, < table size
		typedef std::function<int(T, int)> HashFunction;
	private:
		DynamicArray<LinkedList<T>*>* table;
		HashFunction hashFunction;

		int itemsCount;

		static const int default_size = 64;
	public:
		HashTable(HashFunction hashFunc, int size = default_size):
			hashFunction(hashFunc), itemsCount(0)
		{
			table = new DynamicArray<LinkedList<T>*>(size);

			for (int i = 0; i < size; i++)
				table->Set(new LinkedList<T>, i);
		}
	public:
		void Add(T item)
		{
			int pos = hashFunction(item, GetCapacity());

			LinkedList<T>* target = table->Get(pos);

			bool isPresented = false;

			auto iter = *target->begin_();

			for (; iter != *target->end_(); ++iter)
			{
				if (*iter == item)
					isPresented = true;
			}

			if(!isPresented)
			{
				target->Append(item);
				itemsCount++;
			}
				
		}

		LinkedList<T>* GetByHash(int hash)
		{
			return table->Get(hash);
		}

		void Remove(T item)
		{}
	public:
		int GetCapacity()
		{
			return table->GetCapacity();
		}
		
	};
}