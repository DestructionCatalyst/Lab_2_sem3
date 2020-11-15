#pragma once

#include <iostream>

#include "HashMap.h"
#include "Coordinates.h"

using namespace dictionary;

using std::cout;
using std::endl;

namespace matrix {
	template<class T>
	class SparseMatrix {
	private:
		IDictionary<Coordinates, T>* values;

		int rows;
		int columns;
	public:
		SparseMatrix(int rows, int columns) :
			rows(rows), columns(columns)
		{
			values = new HashMap<Coordinates, T>(coordinatesHash);
		}
		//arr must be an two-dimensional array with size rows*columns
		SparseMatrix(T* arr, int rows, int columns) :
			SparseMatrix(rows, columns)
		{
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					if (arr[i * rows + j] != 0)
						values->Add(Coordinates(i, j), arr[i * rows + j]);
		}

	public:
		T Get(int row, int column) const
		{
			try
			{
				return values->Find(Coordinates(row, column));
			}
			catch (key_not_found)
			{
				return T();
			}
		}
		//TODO remake with map/reduce, prob fix line length
		void Print() const
		{
			for (int i = 0; i < rows; i++) {
				cout << "|| ";
				for (int j = 0; j < columns; j++)
				{
					cout << Get(i, j) << " ";
				}
				cout << "||" << endl;
			}
		}
	public:
		//Order is pretty much random
		void Map(std::function<T(T)> f)
		{
			HashMapIterator<Coordinates, T> iter = dynamic_cast<HashMap<Coordinates, T>*>(values)->Iterator();

			for (; iter != HashMap<Coordinates, T>::iterator(); ++iter)
				values->Add((*iter).first, f((*iter).second));
		}

		friend SparseMatrix<T> operator+ (const SparseMatrix<T>& m1, const SparseMatrix<T>& m2);
	};

	class MatrixSizeMismatchException : public std::invalid_argument
	{
	public:
		MatrixSizeMismatchException(const char* message):
			std::invalid_argument(message)
		{}
	};

	template<class T>
	SparseMatrix<T> operator+(const SparseMatrix<T>& m1, const SparseMatrix<T>& m2)
	{
		if (m1.rows != m2.rows)
			throw MatrixSizeMismatchException("Row count doesn't match, addition is impossible");
		if (m1.columns != m2.columns)
			throw MatrixSizeMismatchException("Column count doesn't match, addition is impossible");

		SparseMatrix<T>* sum = new SparseMatrix<T>(m1.rows, m1.columns);

		

		return SparseMatrix<T>();
	}
}