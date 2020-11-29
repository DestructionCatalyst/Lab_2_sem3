#pragma once

#include "IDictionary.h"
#include "HashMapIterator.h"
#include "ParseFunctions.h"
#include "PairInOut.h"

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
		typedef HashMapIterator<K, V> iterator;
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
		virtual void Add(KeyValuePair pair)
		{
			int hash = Hash(pair.first);

			LinkedList<KeyValuePair>* target = table->Get(hash);

			SameHashIterator iter = FindExactItem(pair.first);

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
		virtual void Add(K key, V value) override
		{
			Add(std::make_pair(key, value));
		}
		virtual void Remove(K key) override
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
		virtual V Get(K key) const override
		{
			SameHashIterator item = FindExactItem(key);
			
			if (item != SameHashIterator(nullptr))
				return (*item).second;
			else
				throw key_not_found("Key is not in dictionary!");
		}
		virtual bool Contains(K key) override
		{
			SameHashIterator item = FindExactItem(key);

			if (item != SameHashIterator(nullptr))
				return true;
			else
				return false;
		}
	public:
		int GetCapacity() const
		{
			return table->GetCapacity();
		}
	public:
		IDictionary<K, V>* Map(std::function<V(V)> f) const
		{
			HashMap<K, V>* res = new HashMap(hashFunction, GetCapacity());

			iterator iter = Iterator();

			for (; iter != End(); ++iter)
				res->Add((*iter).first, f((*iter).second));

			return res;
		}
	private:
		int Hash(K key) const
		{
			return hashFunction(key, GetCapacity());
		}
		//Returns iterator at the KeyValuePair with this key or target->end() if it's not in this map  
		SameHashIterator FindExactItem(K key) const 
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
		double FillCoefficient() const
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
		iterator Iterator() const
		{
			return HashMapIterator<K, V>(table);
		}
		iterator End() const
		{
			return HashMapIterator<K, V>();
		}
	public:
		//template<class K1, class V1>
		//friend std::ostream& operator<<(std::ostream& out, HashMap<K1, V1>& map);
		//Map must have the right type and be initialized with the right hash function
		//template<class K1, class V1>
		//friend std::istream& operator>>(std::istream& in, HashMap<K1, V1>& map);
	public:
		~HashMap()
		{
			for (int i = 0; i < GetCapacity(); i++)
				delete(table->Get(i));

			delete(table);
		}
	};
	
}

template<class K1, class V1>
std::ostream& operator<<(std::ostream& out, const dictionary::HashMap<K1, V1>& hashMap)
{
	out << "{ ";

	dictionary::HashMapIterator<K1, V1> iter = hashMap.Iterator();

	for (; iter != hashMap.End(); ++iter)
	{
		out << *iter << " ";
	}

	out << "}";

	return out;
}

//Map must have the right type and be initialized with the right hash function
template<class K1, class V1>
std::istream& operator>>(std::istream& in, dictionary::HashMap<K1, V1>& map)
{
	string tmp;

	in >> tmp;

	EnsureFirst(tmp, '{');

	std::pair<K1, V1> tmpPair;
	
		while (tmp != "}")
		{
			try
			{
				in >> tmpPair;
			}
			catch (...)
			{
				break;
			}
			map.Add(tmpPair);
		}

	return in;
}