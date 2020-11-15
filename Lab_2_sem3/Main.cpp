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

#include <Windows.h>


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

	TestEnvironment::Assert(
		list->Get(0) == 1 &&
		list->Get(1) == 2 &&
		list->Get(2) == 4 &&
		list->Get(3) == 5 &&
		list->Get(4) == 6 &&
		list->GetLength() == 5 &&

		smallList->GetLength() == 0
	);

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

	TestEnvironment::Assert(
		map->Find(1) == string("aaaa") &&
		map->Find(2) == string("bbbbbb") &&
		map->Find(3) == string("aaa") &&
		map->Find(68) == string("ddd")
	);

	//HashMap<int, string>::iterator iter = dynamic_cast<HashMap<int, string>*>(map)->Iterator();

	//for (; iter != HashMap<int, string>::iterator(); ++iter)
		//std::cout << (*iter).second << std::endl;

	TestEnvironment::AssertThrows(
		[&]()->void
		{
			map->Find(65);
		},
		key_not_found("")
	);
	TestEnvironment::AssertThrows(
		[&]()->void
		{
			map->Find(66);
		},
		key_not_found("")
			);

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

	TestEnvironment::Assert(
		map->Find(1) == string("aaaa") &&
		map->Find(2) == string("bbbbbb") &&
		map->Find(3) == string("aaa") &&
		map->Find(68) == string("ddd")
	);

	TestEnvironment::AssertThrows(
		[&]()->void
		{
			map->Find(65);
		},
		key_not_found("")
			);
	TestEnvironment::AssertThrows(
		[&]()->void
		{
			map->Find(66);
		},
		key_not_found("")
			);

	delete(map);
}

void CoordsTest()
{
	Coordinates c{ 6, 11 };

	int actual = coordinatesHash(c, 8);
	int expected = 7;

	TestEnvironment::Assert(expected == actual);
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

	m.Map(
		[](int n) -> int
		{
			return n * 2;
		}
	);

	m.Print();
}

int main() {


	HashMap<int, string> map1 = HashMap<int, string>([](int s, int a)->int {return
	s % a
	;}, 4);

	map1.Add(1, string("aaaa"));
	map1.Add(2, string("bbb"));
	map1.Add(3, string("aaa"));
	map1.Add(65, string("ccc"));
	map1.Add(68, string("ddd"));
	map1.Add(2, string("bbbbbb"));

	map1.Remove(65);
	
	TestEnvironment env{};

	ADD_NEW_TEST(env, "List remove test", TestListRemove);
	ADD_NEW_TEST(env, "Simple map test", SimpleMapTest);
	ADD_NEW_TEST(env, "Resize map test", ResizeTest);
	ADD_NEW_TEST(env, "Matrix coordinates test", CoordsTest);
	ADD_NEW_TEST(env, "Simple Matrix test", SimpleMatrixTest);

	env.RunAll();
	

	return 0;
}