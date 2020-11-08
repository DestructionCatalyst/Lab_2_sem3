#pragma once
#include <vector>

#include "UnitTest.h"


#define ADD_NEW_TEST(env, name, test) env.AddTest(new UnitTest(name, test))

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
	static void AssertThrows(function<void()> thrower, std::exception exceptionType);
private:
	void PrintResults(int testsPassed);
public:
	~TestEnvironment();
	
};

