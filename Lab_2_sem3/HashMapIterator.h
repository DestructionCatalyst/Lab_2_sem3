#pragma once
#include "dependencies/DynamicArray.h"
#include "dependencies/LinkedList.h"
using namespace sequences;

namespace dictionary {
	template<class K, class V>
	class HashMapIterator
	{
	public:
		typedef std::pair<K, V> KeyValuePair;
		typedef DynamicArray<LinkedList<KeyValuePair>*> HashTable;
		typedef sequences::iterators::MutableListIterator<KeyValuePair> SameHashIterator;
	private:
		HashTable* table;
		int currentHash;
		int tableSize;
		SameHashIterator currentItem;
	public:
		HashMapIterator() :
			table(nullptr), currentHash(0), tableSize(0), currentItem(nullptr)
		{}
		HashMapIterator(HashTable* t):
			table(t), currentHash(0), tableSize(t->GetCapacity()), currentItem(nullptr)
		{
			currentItem = NextHash();
		}
	public:
		HashMapIterator& operator++() 
		{
			NextItem();
			return *this;
		}
		KeyValuePair operator*() const 
		{
			return *currentItem;
		}
		bool operator== (const HashMapIterator<K, V>& o) const 
		{
			return currentItem == o.currentItem;
		}
		bool operator!=(const HashMapIterator<K, V>& o) const 
		{
			return !(*this == o);
		}
	private:
		SameHashIterator NextItem()
		{
			++currentItem;

			if (currentItem == SameHashIterator(nullptr))
			{
				currentHash++;
				currentItem = NextHash();
			}

			return currentItem;

			
		}
		SameHashIterator NextHash()
		{
			if (currentHash >= tableSize)
				return nullptr;

			LinkedList<KeyValuePair>* target = table->Get(currentHash);

			while (target->begin() == target->end())
			{
				currentHash++;
					
				if (currentHash >= tableSize)
					return nullptr;

				target = table->Get(currentHash);
			}
			return target->begin();
		}

	};
}