#pragma once

#include <algorithm>
#include <utility>

#include "dependencies/ArraySequence.h"
#include "SparseMatrix.h"
#include "MatrixFunctions.h"



using namespace sequences;
using std::pair;

namespace matrix {

	class ZeroMatrixException : public std::exception
	{
	public:
		ZeroMatrixException():
			std::exception()
		{}
	};

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

			needed->Append(0);
			needed->Append(1);

			for (int i = 2; i < coef->GetLength(); i++)
			{
				if (coef->Get(i) != 0)
					needed->Append(i);
			}

			curNeeded = 2;
			recountStart = 2;
		}
		SparseMatrix<T>* Calculate()
		{
			CalculatePowers();

			SparseMatrix<T>* res = new SparseMatrix<T>(*zeros);
			SparseMatrix<T>* term = new SparseMatrix<T>(1, 1);

			for (int i = 0; i < needed->GetLength(); i++)
			{
				//std::cout << *matrixPowers;

				*term = coef->Get(needed->Get(i)) * (*matrixPowers->Get(needed->Get(i)));

				*res = (*res) + (*term);
			}

			return res;
		}
	public:
		int CountCost(int leftParent, int rightParent)
		{
			if(leftParent == rightParent)
				return costs->Get(leftParent) + 1;
			else
				return costs->Get(leftParent) + costs->Get(rightParent) + 1;
		}
		//Finds ways with minimal costs in the interval [recountStart, needed.Get(curNeeded)]
		void UpdatePaths()
		{
			int finish = GetNeeded();

			for (int i = recountStart; i <= finish; i++)
			{
				if (costs->Get(i) > 1)
				{
					Recount(i);
				}
			}

			recountStart = finish + 1;

			//std::cout << *costs << std::endl;
		}
		//Get a matrix power, calculating everything with the current parents 
		SparseMatrix<T>* GetPower(int index)
		{
			if (costs->Get(index) == 0)
			{ }
			else if (costs->Get(index) == 1)
			{
				Multiply(parents->Get(index).first, parents->Get(index).second);
			}
			else
			{
				GetPower(parents->Get(index).first);
				GetPower(parents->Get(index).second);
				Multiply(parents->Get(index).first, parents->Get(index).second);
			}

			return matrixPowers->Get(index);

		}
		//Call only if the costs under the indexes are zero
		void Multiply(int leftIndex, int rightIndex)
		{
			int index = leftIndex + rightIndex;

			SparseMatrix<T>* product = new SparseMatrix<T>(
				(*matrixPowers->Get(leftIndex)) * (*matrixPowers->Get(rightIndex))
				);

			matrixPowers->Set(product, index);

			if ((*product) == (*zeros))
				throw ZeroMatrixException();

			costs->Set(0, index);

			recountStart = std::min(recountStart, index);
		}
		void CalculatePowers()
		{
			bool gotZero = false;

			for (; curNeeded < needed->GetLength(); curNeeded++)//2
			{
				if (!gotZero)
				{
					UpdatePaths();
					try {
						GetPower(GetNeeded());
					}
					catch (ZeroMatrixException e)
					{
						gotZero = true;
					}
				}
				else
					matrixPowers->Set(zeros, curNeeded);
			}
		}
		int GetNeeded()
		{
			return needed->Get(curNeeded);
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