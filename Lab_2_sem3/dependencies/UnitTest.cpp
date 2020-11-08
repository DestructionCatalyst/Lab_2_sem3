#include "UnitTest.h"
//#define CATCH_EXCEPTIONS

UnitTest::UnitTest(int id, string name, ITestCase* testCase) :
	id(id), name(name), testCase(testCase)
{}

UnitTest::UnitTest(int id, string name, test_function_t testFunction):
	id(id), name(name), testCase(new TestCase(testFunction))
{}

UnitTest::UnitTest(string name, test_function_t testFunction) :
	name(name), testCase(new TestCase(testFunction))
{
	id = rand();
}

string UnitTest::ConvertResult(TestResult result)
{
	switch (result) {
	case TEST_SUCCESS:
		return "passed!";
	case TEST_FAILURE:
		return "not passed!";
	case TEST_CRASH:
		return "caused an exception!";
	}
	return "";
}

bool UnitTest::Run()
{
	try
	{
		testCase->Execute();
		PrintResult(TEST_SUCCESS);
		return true;
	}
	catch (AssertionException e)
	{
		PrintResult(TEST_FAILURE);
	}
#ifdef CATCH_EXCEPTIONS
	catch (...)
		{
			PrintResult(TEST_CRASH);
		}
#endif // CATCH_EXCEPTIONS
	
	return false;

}

void UnitTest::PrintResult(TestResult result)
{
	std::cout << GenerateResultString(result) << std::endl;
}

string UnitTest::GenerateResultString(TestResult result)
{
	return (std::stringstream() << "Test " << id << " (" << name << ") " << ConvertResult(result)).str();
}

UnitTest::~UnitTest()
{
	delete(testCase);
}