#include "dependencies/TestEnvironment.h"
#include "dependencies/UnitTest.h"
#include "dependencies/TimedTest.h"
#include "dependencies/Timer.h"

#include "FileMacros.h"

#include "Tests.h"

void initTests(TestEnvironment& env)
{
	ADD_NEW_TEST(env, "List remove test", testListRemove);
	ADD_NEW_TEST(env, "Simple map test", simpleMapTest);
	ADD_NEW_TEST(env, "Resize map test", resizeTest);
	ADD_NEW_TEST(env, "Matrix coordinates test", coordsTest);
	ADD_NEW_TEST(env, "Simple Matrix test", simpleMatrixTest);
	ADD_NEW_TEST(env, "Matrix addition test", matrixAdditionTest);
	ADD_NEW_TEST(env, "Matrix on scalar multiplication test", matrixOnScalarMultiplicationTest);
	ADD_NEW_TEST(env, "Matrix multiplication test", matrixMultiplicationTest);
	ADD_NEW_TEST(env, "Matrix power test", matrixPowerTest);
	ADD_NEW_TEST(env, "File reading/writing test", fileTest);
	ADD_NEW_TEST(env, "Matrix polynom test", polynomTest);
}

SparseMatrix<int>* generateMatrix(int dimension, int max, double nonZeroPart)
{
	srand(clock());

	SparseMatrix<int>* res = new SparseMatrix<int>(dimension);

	int nonZeros = dimension * dimension * nonZeroPart;

	for (int i = 0; i < nonZeros; i++)
	{
		res->Set(rand() % dimension, rand() % dimension, rand() % max);
	}

	return res;
}

using std::cout;
using std::cin;
using std::endl;

void header()
{
	cout << "1 - generate matrix" << endl
		<< "2 - show matrix" << endl
		<< "3 - insert polynom coeffitients" << endl
		<< "4 - show coeffitients" << endl
		<< "5 - calculate polynom" << endl
		<< "6 - save to file" << endl
		<< "7 - load from file" << endl
		<< "8 - launch tests" << endl
		<< "0 - exit" << endl << endl;
}

int main() {

	int command = -1;

	int size = 1;
	int max = 1;
	double nonZeroPart = 0.1;

	SparseMatrix<int>* matrix = nullptr;
	ArraySequence<int>* coef = nullptr;
	MatrixPolynom<int>* poly = nullptr;

	TestEnvironment env{};
	initTests(env);

	while (command != 0)
	{
		header();

		try
		{
			std::cin >> command;
		}
		catch (...)
		{
			command = -1;
		}

		switch (command) {
		case 1:
			try
			{
				cout << "Insert matrix dimension: " << endl;
				cin >> size;

				cout << "Insert maximum item value: " << endl;
				cin >> max;

				cout << "Insert part of non-zero items (e.g. 0.1 = 10%): " << endl;
				cin >> nonZeroPart;

				delete(matrix);

				matrix = generateMatrix(size, max, nonZeroPart);
			}
			catch (...)
			{
				command = -1;
			}
			break;
		case 2:
			if (matrix == nullptr)
				std::cout << "Not initialized!" << endl;
			else
				std::cout << *matrix << endl;

			break;
		case 3:
			try
			{
				cout << "Insert polynom coeffitients: " << endl;

				delete(coef);

				coef = new ArraySequence<int>();
				
				std::cin >> *coef;
			}
			catch (...)
			{
				command = -1;
			}

			break;
		case 4:
			if (coef == nullptr)
				std::cout << "Not initialized!" << endl;
			else
				std::cout << *coef << endl << endl;

			break;
		case 5:
			if ((coef == nullptr) || (matrix == nullptr))
				std::cout << "Not initialized!" << endl;
			else
			{
				poly = new MatrixPolynom<int>(matrix, coef);
				Timer t{};
				t.Start();
				SparseMatrix<int>* res = poly->Calculate();
				t.Pause();
				std::cout << *res << "Calculated in " << t.GetMS() << " ms" << std::endl;
			}

			break;
		case 6:
			if ((coef == nullptr) || (matrix == nullptr))
				std::cout << "Not initialized!" << endl;
			else 
			{
				WRITE_TO_FILE(*matrix, "matrix_.txt");
				WRITE_TO_FILE(*coef, "coeffitients.txt");
			}

			break;
		case 7:
			matrix = new SparseMatrix<int>(1);
			coef = new ArraySequence<int>();
			READ_FROM_FILE(*matrix, "matrix_.txt");
			READ_FROM_FILE(*coef, "coeffitients.txt");

			break;
		case 8:
			env.RunAll();

			break;
		case 0:
			break;
		default:
			cout << "Incorrect input!" << endl;
		}

	}
	
	delete(matrix);
	delete(coef);
	delete(poly);

	return 0;
}