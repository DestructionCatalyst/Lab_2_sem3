#pragma once

#include "IDictionary.h"

#include "dependencies/DynamicArray.h"
#include "dependencies/LinkedList.h"
using namespace sequences;

namespace dictionary
{
	class key_not_found : public std::invalid_argument
	{
	public:
		key_not_found(const char* message) :
			std::invalid_argument(message)
		{}
	};

	template<class K, class V>
	class HashMap : public IDictionary<K,V>
	{
	public:
		typedef std::pair<K, V> KeyValuePair;
		//Hash function takes an item and a table size, and returns an index, < table size
		typedef std::function<int(K, int)> HashFunction;
		typedef sequences::iterators::MutableListIterator<KeyValuePair> SameHashIterator;
	private:
		DynamicArray<LinkedList<KeyValuePair>*>* table;
		HashFunction hashFunction;

		int itemsCount;

		static const int default_size = 64;
	public:
		HashMap(HashFunction hashFunc, int size = default_size) :
			hashFunction(hashFunc), itemsCount(0)
		{
			table = new DynamicArray<LinkedList<KeyValuePair>*>(size);

			for (int i = 0; i < size; i++)
				table->Set(new LinkedList<KeyValuePair>, i);
		}
	public:
		virtual void Add(K key, V value)
		{
			int hash = Hash(key);

			LinkedList<KeyValuePair>* target = table->Get(hash);

			SameHashIterator iter = FindExactItem(key);

			KeyValuePair pair = std::make_pair(key, value);

			if (iter == target->end())
			{
				target->Append(pair);
				itemsCount++;
			}
			else
			{
				iter.SetContent(pair);
			}

			Grow();
		}
		virtual void Remove(K key)
		{
			int listIndex = Hash(key);

			int itemIndex = 0;

			LinkedList<KeyValuePair>* target = table->Get(listIndex);

			SameHashIterator iter = target->begin();

			while ((iter != target->end()) && ((*iter).first != key))
			{
				++itemIndex;
				++iter;
			}

			if (iter != target->end())
				target->Remove(itemIndex);

			itemsCount--;

			Shrink();
		}
		virtual V Find(K key)
		{
			SameHashIterator item = FindExactItem(key);
			
			if (item != SameHashIterator(nullptr))
				return (*item).second;
			else
				throw key_not_found("Key is not in dictionary!");
		}
	public:
		int GetCapacity()
		{
			return table->GetCapacity();
		}
		
	private:
		int Hash(K key)
		{
			return hashFunction(key, GetCapacity());
		}
		//Returns iterator at the KeyValuePair with this key or target->end() if it's not in this map  
		SameHashIterator FindExactItem(K key)
		{
			int hash = Hash(key);

			LinkedList<KeyValuePair>* target = table->Get(hash);

			SameHashIterator iter = target->begin();

			while ((iter != target->end()) && ((*iter).first != key))
			{
				++iter;
			}

			return iter;
		}
		double FillCoefficient()
		{
			return (double)itemsCount / GetCapacity();
		}
		void Grow()
		{
			if (FillCoefficient() > 0.75)
				Resize(GetCapacity() * 2);
		}
		void Shrink()
		{
			if (GetCapacity() > default_size && FillCoefficient() < 0.5)
				Resize(GetCapacity() / 2);
		}
		void Resize(int newSize)
		{
			DynamicArray<LinkedList<KeyValuePair>*>* oldTable = table;
			table = new DynamicArray<LinkedList<KeyValuePair>*>(newSize);

			for (int i = 0; i < newSize; i++)
				table->Set(new LinkedList<KeyValuePair>, i);

			LinkedList<KeyValuePair>* cur;
			SameHashIterator iter = nullptr;
			KeyValuePair curPair;

			itemsCount = 0;

			for (int i = 0; i < oldTable->GetCapacity(); i++)
			{
				cur = oldTable->Get(i);

				for (iter = cur->begin(); iter != cur->end(); ++iter)
				{
					curPair = *iter;
					Add(curPair.first, curPair.second);
				}
				
			}
		}
	public:
		~HashMap()
		{
			for (int i = 0; i < GetCapacity(); i++)
				delete(table->Get(i));

			delete(table);
		}
	};
	
	
}

