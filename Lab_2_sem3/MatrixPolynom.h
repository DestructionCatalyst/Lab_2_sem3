#pragma once

#include <algorithm>
#include <utility>

#include "dependencies/ArraySequence.h"
#include "SparseMatrix.h"
#include "MatrixFunctions.h"

using namespace sequences;
using std::pair;

namespace matrix {
	template<class T>
	class MatrixPolynom 
	{
	public:
		ArraySequence<SparseMatrix<T>*>* matrixPowers;//
		SparseMatrix<T>* zeros;//
		ArraySequence<T>* coef;//

		ArraySequence<int>* costs;//
		ArraySequence<pair<int, int>>* parents;//
		ArraySequence<int>* needed;//

		int curNeeded;
		int recountStart;

	public:
		MatrixPolynom(SparseMatrix<T>* matrix, ArraySequence<T>* coef) :
			coef(coef)
		{
			if (matrix->GetRows() != matrix->GetColumns())
				throw MatrixSizeException("");

			int length = coef->GetLength();

			matrixPowers = new ArraySequence<SparseMatrix<T>*>(length);

			matrixPowers->Append(make_identity<T>(matrix->GetRows()));
			matrixPowers->Append(matrix);

			for(int i = 2; i < length; i++)
				matrixPowers->Append(nullptr);

			zeros = make_zeros<T>(matrix->GetRows(), matrix->GetColumns());

			costs = new ArraySequence<int>(length);

			costs->Append(0);
			costs->Append(0);

			for (int i = 2; i < length; i++)
				costs->Append(i - 1);

			

			parents = new ArraySequence<pair<int, int>>(length);

			parents->Append(std::make_pair(0, 0));
			parents->Append(std::make_pair(0, 1));

			for (int i = 2; i < length; i++)
				parents->Append(std::make_pair(1, i - 1));

			needed = new ArraySequence<T>();

			for (int i = 0; i < coef->GetLength(); i++)
			{
				if (coef->Get(i) != 0)
					needed->Append(i);
			}

			curNeeded = 0;
			recountStart = 2;
		}
	public:
		int CountCost(int leftParent, int rightParent)
		{
			if(leftParent == rightParent)
				return costs->Get(leftParent) + 1;
			else
				return costs->Get(leftParent) + costs->Get(rightParent) + 1;
		}
		void UpdatePaths()
		{
			int finish = needed->Get(curNeeded);

			for (int i = recountStart; i <= finish; i++)
			{
				if (costs->Get(i) > 1)
				{
					Recount(i);
				}
			}
		}
	private:
		void Recount(int index)
		{
			int left = 1;
			int right = index - 1;

			while (left <= right)
			{
				int newCost = CountCost(left, right);

				if (newCost < costs->Get(index))
				{
					costs->Set(newCost, index);
					parents->Set(std::make_pair(left, right), index);

					if (newCost < 2)
						break;
				}

				left++;
				right--;

			}
		}
	};
}