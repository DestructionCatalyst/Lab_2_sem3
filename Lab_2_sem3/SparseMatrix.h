#pragma once

#include <sstream>
#include <utility>

#include "HashMap.h"
#include "Coordinates.h"

using namespace dictionary;

using std::pair;

namespace matrix {

	class MatrixSizeException : public std::invalid_argument
	{
	public:
		MatrixSizeException(const char* message) :
			std::invalid_argument(message)
		{}
	};

	template<class T>
	class SparseMatrix {
	public:
		typedef HashMapIterator<Coordinates, T> iterator;
	private:
		IDictionary<Coordinates, T>* values;

		int rows;
		int columns;
	public:
		SparseMatrix(int rows, int columns) :
			rows(rows), columns(columns)
		{
			if (rows <= 0 || columns <= 0)
				throw MatrixSizeException("Matrix dimensions can't be zero or negative!");
			values = new HashMap<Coordinates, T>(coordinatesHash);
		}
		//arr must be an two-dimensional array with size rows*columns
		SparseMatrix(T* arr, int rows, int columns) :
			SparseMatrix(rows, columns)
		{
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					if (arr[i * columns + j] != 0)
						values->Add(Coordinates(i, j), arr[i * columns + j]);
		}
		SparseMatrix(const SparseMatrix<T>& m) :
			SparseMatrix(m.rows, m.columns)
		{
			m.ForEach(
				[&](Coordinates coord, T item)->void
				{
					values->Add(coord, item);
				}
			);
		}

	public:
		T Get(Coordinates coord) const
		{
			try
			{
				return values->Find(coord);
			}
			catch (key_not_found)
			{
				return T();
			}
		}
		T Get(int row, int column) const
		{
			return Get(Coordinates(row, column));
		}
		void Set(Coordinates coord, T item)
		{
			if (coord.GetRow() < rows && coord.GetColumn() < columns)
			{
				if (item == T())
					values->Remove(coord);
				else
					values->Add(coord, item);
			}	
			else
				throw MatrixSizeException("Coordinates are out of the matrix!");
		}
		void Set(int row, int column, T item)
		{
			Set(Coordinates(row, column), item);
		}
		int GetRows()
		{
			return rows;
		}
		int GetColumns()
		{
			return columns;
		}
	public:
		//Order is pretty much random
		SparseMatrix<T> Map(std::function<T(T)> f)
		{
			SparseMatrix<T>* res = new SparseMatrix<T>(rows, columns);

			IDictionary<Coordinates, T>* resValues = values->Map(f);

			res->values = resValues;

			return *res;
		}
		T Reduce(std::function<T(T, T)> f, T startItem) const
		{
			T result = startItem;

			iterator iter = Iterator();

			for (; iter != End(); ++iter)
				result = f((*iter).second, result);

			return result;
		}
	private:
		//For operations that don't change matrix items
		void ForEach(std::function<void(Coordinates, T)> f) const
		{
			iterator iter = Iterator();

			for (; iter != End(); ++iter)
				f((*iter).first, (*iter).second);
		}
		//Processes row-by-row, including zeros. Executes betweenRows(int) after each row, passing current row number
		void FullForEach(std::function<void(T)> f, std::function<void(int)> betweenRows = [](int)->void {}) const
		{
			for (int i = 0; i < rows; i++)////////////////////////
			{
				for (int j = 0; j < columns; j++)////////////////////////
					f(Get(i, j));

				betweenRows(i);
			}
		}
	
		

	public:
		iterator Iterator() const
		{
			return dynamic_cast<HashMap<Coordinates, T>*>(values)->Iterator();
		}
		iterator End() const
		{
			return HashMap<Coordinates, T>::iterator();
		}
	public:
		template<class T1>
		friend SparseMatrix<T1> operator+ (const SparseMatrix<T1>& m1, const SparseMatrix<T1>& m2);

		template<class T1>
		friend std::ostream& operator<< (std::ostream& stream, const SparseMatrix<T1>& matrix);

		template<class T1>
		friend bool operator== (const SparseMatrix<T1>& m1, const SparseMatrix<T1>& m2);

		template<class T1>
		friend bool operator!= (const SparseMatrix<T1>& m1, const SparseMatrix<T1>& m2);
	};

	

	template<class T>
	int PrintedItemLength(T item)
	{
		std::stringstream s;

		s << item;

		s.seekg(0, std::ios::end);
		 
		return s.tellg();
	}

	template<class T>
	int GetMaxLength(SparseMatrix<T> m) 
	{
		T maxLenItem = m.Reduce(
			[&](T a, T b)->T
			{
				if (PrintedItemLength(a) > PrintedItemLength(b))
					return a;
				else
					return b;
			},
			T()
				);

		return PrintedItemLength(maxLenItem);
	}

	template<class T>
	string AddSpacing(T item, int maxLength)
	{
		int length = PrintedItemLength(item);

		std::stringstream res{};

		for (int i = length; i <= maxLength; i++)
		{
			res << " ";
		}

		res << item;

		return res.str();
	}

	template<class T>
	std::ostream& operator<< (std::ostream& stream, const SparseMatrix<T>& matrix)
	{
		int maxLength = GetMaxLength(matrix);

		stream << "||";

		matrix.FullForEach(
			[&](T item)->void
			{
				stream << AddSpacing(item, maxLength);
			},
			[&](int rowNumber)->void
			{
				stream << " ||\n";

				if (rowNumber != matrix.rows - 1)
					stream << "||";
			}
			);

		return stream;
	}
	

	template<class T>
	SparseMatrix<T> operator+(const SparseMatrix<T>& m1, const SparseMatrix<T>& m2)
	{
		if (m1.rows != m2.rows)
			throw MatrixSizeException("Row count doesn't match, addition is impossible");
		if (m1.columns != m2.columns)
			throw MatrixSizeException("Column count doesn't match, addition is impossible");

		SparseMatrix<T>* sum = new SparseMatrix<T>(m1);

		m2.ForEach(
			[&](Coordinates c, T item)->void
			{
				T itemSum = item + m1.Get(c);

				sum->Set(c, itemSum);
			}
		);

		return *sum;
	}

	template<class T>
	bool operator==(const SparseMatrix<T>& m1, const SparseMatrix<T>& m2)
	{

		if (m1.rows != m2.rows)
			throw MatrixSizeException("Row count doesn't match, comparsion is impossible");
		if (m1.columns != m2.columns)
			throw MatrixSizeException("Column count doesn't match, comparsion is impossible");

		bool equal = true;

		m1.ForEach(
			[&](Coordinates c, T value)->void
			{
					equal = equal && (value == m2.Get(c));
			}
		);

		m2.ForEach(
			[&](Coordinates c, T value)->void
			{
				equal = equal && (value == m1.Get(c));
			}
		);

		return equal;
	}

	template<class T1>
	bool operator!=(const SparseMatrix<T1>& m1, const SparseMatrix<T1>& m2)
	{
		return !(m1 == m2);
	}
}