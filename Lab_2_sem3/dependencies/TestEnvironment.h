#pragma once
#include <vector>

#include "UnitTest.h"


#define ADD_NEW_TEST(TEST_ENVIRONMENT, TEST_NAME, TEST_FUNCTION) TEST_ENVIRONMENT.AddTest\
																	(new UnitTest(TEST_NAME, TEST_FUNCTION));

#define ASSERT_EQUALS(EXPRESSION1, EXPRESSION2) TestEnvironment::Assert((EXPRESSION1) == (EXPRESSION2));
#define ASSERT_NOT_EQUALS(EXPRESSION1, EXPRESSION2) TestEnvironment::Assert((EXPRESSION1) != (EXPRESSION2));

#define ASSERT_THROWS(EXPRESSION, EXCEPTION_TYPE) {bool thrown = false;\
												try{EXPRESSION;}\
												catch (EXCEPTION_TYPE ex){ thrown = true; }\
												TestEnvironment::Assert(thrown);}

using std::vector;

class TestEnvironment
{
private:
	vector<UnitTest*> tests{};
public:
	TestEnvironment& AddTest(UnitTest* testToAdd);
	void Run(int testIndex);
	void RunAll();
public:
	static void Assert(int expression);
	static void AssertThrows(function<void()> thrower, std::exception&& exceptionType);
private:
	void PrintResults(int testsPassed);
public:
	~TestEnvironment();
	
};

