#pragma once
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <new>


namespace sequences {

	template <class T> class DynamicArray {

	private:

		T* elements;

		int capacity;

	public:

		DynamicArray(int size):
			capacity(size)
		{
			elements = (T*)malloc(capacity * sizeof(T));
		}

		DynamicArray(T* items, int count):
			DynamicArray(count)
		{
			memcpy(elements, items, count * sizeof(T));
		}

		//WARNING shallow copy
		DynamicArray(const DynamicArray<T>& dynamicArray):
			DynamicArray(dynamicArray.capacity)
		{
			memcpy(elements, dynamicArray.elements, capacity * sizeof(T));
		}
		//TODO конструктор с initializer list
	public:

		T Get(int index) const 
		{
			if ((index < 0) || (index >= capacity))
				throw std::out_of_range("Array index is out of bounds");
			else
				return elements[index];
		}

		int GetCapacity() const
		{
			return capacity;
		}

	public:

		void Set(T value, int index)
		{
			if ((index < 0) || (index >= capacity))
				throw std::out_of_range("Array index is out of bounds");
			else
				elements[index] = value;
		}

		void Resize(int newSize)
		{

			if (newSize < 0)
				throw std::bad_array_new_length();

			T* newElements = (T*)realloc(elements, newSize * sizeof(T));
			
			if (newElements) {
				elements = newElements;
				capacity = newSize;
			}
			else
				throw std::exception("Not enough memory!");

		}

	public:

		~DynamicArray()
		{
			//free(elements);
			delete[] elements;
		}
	};
}
