#include "Tests.h"

void testListRemove()
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

void simpleMapTest()
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

	ASSERT_EQUALS(map->Get(1), string("aaaa"));
	ASSERT_EQUALS(map->Get(2), string("bbbbbb"));
	ASSERT_EQUALS(map->Get(3), string("aaa"));
	ASSERT_EQUALS(map->Get(68), string("ddd"));

	//HashMap<int, string>::iterator iter = dynamic_cast<HashMap<int, string>*>(map)->Iterator();

	//for (; iter != HashMap<int, string>::iterator(); ++iter)
		//std::cout << (*iter).second << std::endl;

	IDictionary<int, string>* map1 = map->Map(
		[](string s)->string
		{
			return s.append("1");
		}
	);

	ASSERT_EQUALS(map1->Get(1), string("aaaa1"));
	ASSERT_EQUALS(map1->Get(2), string("bbbbbb1"));
	ASSERT_EQUALS(map1->Get(3), string("aaa1"));
	ASSERT_EQUALS(map1->Get(68), string("ddd1"));

	ASSERT_THROWS(map->Get(65), key_not_found);
	ASSERT_THROWS(map->Get(66), key_not_found);

	delete(map);

}

void resizeTest()
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

	ASSERT_EQUALS(map->Get(1), string("aaaa"));
	ASSERT_EQUALS(map->Get(2), string("bbbbbb"));
	ASSERT_EQUALS(map->Get(3), string("aaa"));
	ASSERT_EQUALS(map->Get(68), string("ddd"));

	ASSERT_THROWS(map->Get(65), key_not_found);
	ASSERT_THROWS(map->Get(66), key_not_found);

	delete(map);
}

void coordsTest()
{
	Coordinates c{ 6, 11 };

	int actual = coordinatesHash(c, 8);
	int expected = 7;

	ASSERT_EQUALS(expected, actual);
}

void simpleMatrixTest()
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

void matrixAdditionTest()
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

void matrixOnScalarMultiplicationTest()
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

void matrixMultiplicationTest()
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

	SparseMatrix<int> mA{ a, 2, 4 };
	SparseMatrix<int> mB{ b, 4, 3 };
	SparseMatrix<int> expected{ exp, 2, 3 };

	//std::cout << mA * mB;

	ASSERT_EQUALS(expected, mA * mB);

	ASSERT_THROWS(m1 * mA, MatrixSizeException);
}

void matrixPowerTest()
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

	ASSERT_EQUALS(*make_diagonal(27, 25), matrix::pow(*make_diagonal(3, 25), 3));

	ASSERT_THROWS(matrix::pow(mA, -10), std::invalid_argument);

	int b[] =
	{
		1, 2
	};

	SparseMatrix<int> mB{ b, 1, 2 };

	ASSERT_THROWS(matrix::pow(mB, 2), MatrixSizeException);
}

void fileTest()
{
	Coordinates c{ 50, 120 };

	WRITE_TO_FILE(c, "coords.txt");

	Coordinates input;

	READ_FROM_FILE(input, "coords.txt");

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

	HashMap<int, string>* hMap = dynamic_cast<HashMap<int, string>*>(map);

	WRITE_TO_FILE(*hMap, "map.txt");

	HashMap<int, string>* inMap = new HashMap<int, string>(
		[](int key, int tableSize)->int
		{
			return key % tableSize;
		}
	);

	READ_FROM_FILE(*inMap, "map.txt");

	//std::cout << *inMap;

	int a[] =
	{
		0, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 5, 0,
		0, 0, -2, 0, 0
	};

	SparseMatrix<int> mA{ a, 4, 5 };

	WRITE_TO_FILE(mA, "matrix.txt");

	SparseMatrix<int> mB{ 1, 1 };

	READ_FROM_FILE(mB, "matrix.txt");

	ASSERT_EQUALS(mA, mB);

}

void polynomTest()
{
	int a[] =
	{
		1, 0, 0, 0, 0,
		3, 1, 0, 0, 9,
		0, 0, 0, 0, 0,
		0, 0, 4, 0, 0,
		0, 0, 5, 0, 0
	};

	SparseMatrix<int>* matrix = new SparseMatrix<int>(a, 5, 5);

	ArraySequence<int>* seq = new ArraySequence<int>({ 1, 1, 0, 0, 0, -2, 0, 0, 0, 1 });

	MatrixPolynom<int>* polynom = new MatrixPolynom<int>(matrix, seq);

	int exp[] = 
	{
		1, 0, 0, 0, 0,
		0, 1, -45, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 4, 1, 0,
		0, 0, 5, 0, 1
	};

	SparseMatrix<int>* mA = polynom->Calculate();

	SparseMatrix<int>* mE = new SparseMatrix<int>(exp, 5, 5);

	//std::cout << *mA << std::endl;

	ASSERT_EQUALS(*mE, *mA);
	
	
}