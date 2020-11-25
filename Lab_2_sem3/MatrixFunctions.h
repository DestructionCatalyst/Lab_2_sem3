#pragma once

#include "SparseMatrix.h"

namespace matrix {

	template<class T>
	SparseMatrix<T>* make_zeros(int rows, int columns)
	{
		return new SparseMatrix<T>(rows, columns);
	}

	template<class T>
	SparseMatrix<T>* make_diagonal(T diagonalItem, int dimension)
	{
		SparseMatrix<T>* res = new SparseMatrix<T>(dimension);

		for (int i = 0; i < dimension; i++)
			res->Set(i, i, diagonalItem);

		return res;
	}

	template<class T>
	SparseMatrix<T>* make_identity(int dimension, T one_in_field = T(1))
	{
		return make_diagonal<T>(one_in_field, dimension);
	}


	template<class T>
	SparseMatrix<T>& pow(const SparseMatrix<T>& m1, int power)
	{
		if (power < 0)
			throw std::invalid_argument("Negative powers not supported");

		if (m1.GetRows() != m1.GetColumns())
			throw MatrixSizeException("Matrix must be square");

		SparseMatrix<T>* res = make_identity<T>(m1.GetRows());

		for (int i = 0; i < power; i++)
		{
			(*res) = (*res) * m1;
		}

		return *res;
	}
}