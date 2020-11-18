#pragma once

#include <functional>

namespace dictionary {
	//K - key type, V - value type
	template<class K, class V>
	class IDictionary
	{
	public:
		virtual void Add(K key, V value) = 0;
		virtual void Remove(K key) = 0;
		virtual V Find(K key) const = 0;

		virtual IDictionary<K, V>* Map(std::function<V(V)>) = 0;
		//TODO reduce
		//TODO zip

		virtual ~IDictionary()
		{};
	};
}