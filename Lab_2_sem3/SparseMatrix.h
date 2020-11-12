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
		HashMap<Coordinates, T>* values;

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
		T Get(int row, int column)
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
		void Print()
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
	};
}