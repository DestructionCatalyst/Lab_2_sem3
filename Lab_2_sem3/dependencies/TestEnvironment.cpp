#include "TestEnvironment.h"

TestEnvironment& TestEnvironment::AddTest(UnitTest* testToAdd)
{
	tests.push_back(testToAdd);
	return *this;
}

void TestEnvironment::Run(int testIndex)
{
	tests[testIndex]->Run();
}

void TestEnvironment::RunAll()
{
	int passed = 0;

	for (UnitTest* test : tests)
	{
		//Add 1 if test is passed
		passed += test->Run();
	}

	PrintResults(passed);
}

void TestEnvironment::PrintResults(int testsPassed)
{
	
	std::cout << std::endl << "Testing finished, passed " << testsPassed << " out of " << tests.size() << std::endl;
}

void TestEnvironment::Assert(int expression)
{
	if (!expression)
		throw AssertionException();
}

void TestEnvironment::AssertThrows(function<void()> thrower, std::exception&& exceptionType)
{
}

TestEnvironment::~TestEnvironment()
{
	for (UnitTest* test : tests)
	{
		delete(test);
	}
}