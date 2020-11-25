#include "dependencies/ArraySequence.h"
#include "dependencies/ListSequence.h"
#include "dependencies/Sequence.h"

#include "dependencies/TestEnvironment.h"
#include "dependencies/UnitTest.h"
#include "dependencies/TimedTest.h"

#include "IDictionary.h"
#include "HashMap.h"

#include "Coordinates.h"
#include "SparseMatrix.h"
#include "MatrixFunctions.h"

#include <fstream>

using namespace dictionary;
using namespace matrix;

void TestListRemove()
{
	int a[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	LinkedList<int>* list = new LinkedList<int>(a, 8);

	list->Remove(3);
	list->Remove(6);
	list->Remove(0);

	LinkedList<int>* smallList = new LinkedList<int>(a, 1);

	smallList->Remove(0);

	ASSERT_EQUALS(list->Get(0), 1);
	ASSERT_EQUALS(list->Get(1), 2);
	ASSERT_EQUALS(list->Get(2), 4);
	ASSERT_EQUALS(list->Get(3), 5);
	ASSERT_EQUALS(list->Get(4), 6);

	ASSERT_EQUALS(list->GetLength(), 5);

	ASSERT_EQUALS(smallList->GetLength(), 0);

	delete(list);
	delete(smallList);
}

void SimpleMapTest()
{

	IDictionary<int, string>* map = new HashMap<int, string>(
		[](int key, int tableSize)->int
		{
			return key % tableSize;
		}
	);
	
	map->Add(1, string("aaaa"));
	map->Add(2, string("bbb"));
	map->Add(3, string("aaa"));
	map->Add(65, string("ccc"));
	map->Add(68, string("ddd"));
	map->Add(2, string("bbbbbb"));

	map->Remove(65);

	ASSERT_EQUALS(map->Find(1), string("aaaa"));
	ASSERT_EQUALS(map->Find(2), string("bbbbbb"));
	ASSERT_EQUALS(map->Find(3), string("aaa"));
	ASSERT_EQUALS(map->Find(68), string("ddd"));

	//HashMap<int, string>::iterator iter = dynamic_cast<HashMap<int, string>*>(map)->Iterator();

	//for (; iter != HashMap<int, string>::iterator(); ++iter)
		//std::cout << (*iter).second << std::endl;

	IDictionary<int, string>* map1 = map->Map(
		[](string s)->string
		{
			return s.append("1");
		}
	);

	ASSERT_EQUALS(map1->Find(1), string("aaaa1"));
	ASSERT_EQUALS(map1->Find(2), string("bbbbbb1"));
	ASSERT_EQUALS(map1->Find(3), string("aaa1"));
	ASSERT_EQUALS(map1->Find(68), string("ddd1"));

	ASSERT_THROWS(map->Find(65), key_not_found);
	ASSERT_THROWS(map->Find(66), key_not_found);

	delete(map);

}

void ResizeTest()
{
	IDictionary<int, string>* map = new HashMap<int, string>(
		[](int key, int tableSize)->int
		{
			return key % tableSize;
		},
		4
	);

	map->Add(1, string("aaaa"));
	map->Add(2, string("bbb"));
	map->Add(3, string("aaa"));
	map->Add(65, string("ccc"));
	map->Add(68, string("ddd"));
	map->Add(2, string("bbbbbb"));

	map->Remove(65);

	ASSERT_EQUALS(map->Find(1),string("aaaa"));
	ASSERT_EQUALS(map->Find(2), string("bbbbbb"));
	ASSERT_EQUALS(map->Find(3), string("aaa"));
	ASSERT_EQUALS(map->Find(68), string("ddd"));

	ASSERT_THROWS(map->Find(65), key_not_found);
	ASSERT_THROWS(map->Find(66), key_not_found);

	delete(map);
}

void CoordsTest()
{
	Coordinates c{ 6, 11 };

	int actual = coordinatesHash(c, 8);
	int expected = 7;

	ASSERT_EQUALS(expected, actual);
}

void SimpleMatrixTest()
{
	int a[] = {
		 0, 0, 0, 0, 1, 0, 0, 2, 0, 0 ,
		 3, 0, 0, 0, 0, 0, 0, 0, 0, 4 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 9, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 5, 5, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 3, 0, 0, 0, 0 ,
		 0, 0, 6, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
	};

	SparseMatrix<int> m = SparseMatrix<int>(a, 10, 10);

	SparseMatrix<int> m1 = *m.Map(
		[](int n) -> int
		{
			return n * 2;
		}
	);

	int sum = m1.Reduce(
		[](int b, int c) -> int
		{
			return b + c;
		},
		0
	);
	
	//std::cout << m1;

	ASSERT_EQUALS(sum, 76);
}

void MatrixAdditionTest()
{
	int a[] =
	{
		0, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 5, 0,
		0, 0, -2, 0, 0
	};

	int b[] =
	{
		0, 0, 0, 0, 8,
		0, 3, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 2, 0, 0
	};

	SparseMatrix<int> mA{ a, 4, 5 };
	SparseMatrix<int> mB{ b, 4, 5 };

	SparseMatrix<int> sum = mA + mB;

	//std::cout << mA << std::endl << mB << std::endl << sum;

	int exp[] =
	{
		0, 0, 0, 0, 8,
		0, 4, 0, 0, 0,
		0, 0, 0, 5, 0,
		0, 0, 0, 0, 0
	};

	SparseMatrix<int> expected{ exp, 4, 5 };

	ASSERT_EQUALS(expected, sum);

	int c[] = { 0, 0, 1, 0 };

	SparseMatrix<int> mC{ c, 2, 2 };

	ASSERT_THROWS(mA + mC, MatrixSizeException);
}

void MatrixOnScalarMultiplicationTest()
{
	int a[] =
	{
		0, 0, 0, 8, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 5, 0,
		0, 0, -2, 0, 0
	};

	int exp[] =
	{
		0, 0, 0, -24, 0,
		0, -3, 0, 0, 0,
		0, 0, 0, -15, 0,
		0, 0, 6, 0, 0
	};

	int scalar = -3;

	SparseMatrix<int> mA{ a, 4, 5 };
	SparseMatrix<int> expected{ exp, 4, 5 };

	ASSERT_EQUALS(expected, scalar * mA);
}

void MatrixMultiplicationTest()
{
	SparseMatrix<int> m1 = *make_identity<int>(6);
	//SparseMatrix<int> m2{ e1, 6, 6 };

	//std::cout << m1 * m1;

	ASSERT_EQUALS(m1, m1 * m1);

	int a[] =
	{
		3, 0, 0, 0,
		0, 2, 1, 0
		
	};

	int b[] =
	{
		0, 1, 0,
		1, 1, 0,
		0, 1, 0,
		1, 0, 0
	};

	int exp[] =
	{
		0, 3, 0,
		2, 3, 0
	};

	SparseMatrix<int> mA { a, 2, 4 };
	SparseMatrix<int> mB{ b, 4, 3 };
	SparseMatrix<int> expected{ exp, 2, 3 };

	//std::cout << mA * mB;

	ASSERT_EQUALS(expected, mA * mB);

	ASSERT_THROWS(m1 * mA, MatrixSizeException);
}

void MatrixPowerTest()
{
	int a[] =
	{
		1, 0, 0, 0, 0,
		3, 1, 0, 0, 9,
		0, 0, 0, 0, 0,
		0, 0, 4, 0, 0,
		0, 0, 5, 0, 0
	};

	SparseMatrix<int> mA{ a, 5, 5 };

	int exp[] = 
	{
		1, 0, 0, 0, 0,
		12, 1, 45, 0, 9,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	};

	SparseMatrix<int> expected{ exp, 5, 5 };

	ASSERT_EQUALS(expected, matrix::pow(mA, 4));

	ASSERT_EQUALS(*make_diagonal(27, 10), matrix::pow(*make_diagonal(3, 10), 3));

	ASSERT_THROWS(matrix::pow(mA, -10), std::invalid_argument);

	int b[] =
	{
		1, 2
	};

	SparseMatrix<int> mB{ b, 1, 2 };

	ASSERT_THROWS(matrix::pow(mB, 2), MatrixSizeException);
}

void FileTest()
{
	Coordinates c{ 50, 120 };

	std::ofstream out("coords.txt",/*std::ios::binary|*/std::ios::out);

	out << c;

	out.close();

	std::ifstream in("coords.txt",/*std::ios::binary|*/std::ios::in);

	Coordinates input;

	in >> input;

	in.close();

	ASSERT_EQUALS(input.GetRow(), 50);
	ASSERT_EQUALS(input.GetColumn(), 120);

	IDictionary<int, string>* map = new HashMap<int, string>(
		[](int key, int tableSize)->int
		{
			return key % tableSize;
		}
	);

	map->Add(1, string("aaaa"));
	map->Add(2, string("bbb"));
	map->Add(3, string("aaa"));
	map->Add(65, string("ccc"));
	map->Add(68, string("ddd"));
	map->Add(2, string("bbbbbb"));

	//std::cout << *dynamic_cast<HashMap<int, string>*>(map);
}

int main() {
	
	TestEnvironment env{};

	ADD_NEW_TEST(env, "List remove test", TestListRemove);
	ADD_NEW_TEST(env, "Simple map test", SimpleMapTest);
	ADD_NEW_TEST(env, "Resize map test", ResizeTest);
	ADD_NEW_TEST(env, "Matrix coordinates test", CoordsTest);
	ADD_NEW_TEST(env, "Simple Matrix test", SimpleMatrixTest);
	ADD_NEW_TEST(env, "Matrix addition test", MatrixAdditionTest);
	ADD_NEW_TEST(env, "Matrix on scalar multiplication test", MatrixOnScalarMultiplicationTest);
	ADD_NEW_TEST(env, "Matrix multiplication test", MatrixMultiplicationTest);
	ADD_NEW_TEST(env, "Matrix power test", MatrixPowerTest);
	ADD_NEW_TEST(env, "File reading/writing test", FileTest);

	env.RunAll();

	return 0;
}