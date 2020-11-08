#pragma once

#include <string>
#include <functional>
#include <random>
#include <iostream>
#include <sstream>

#include "AssertionException.h"
#include "ITestCase.h"
#include "TestCase.h"

using std::string; 

class UnitTest
{
public:
	typedef std::function<void()> test_function_t;

private:
	int id;
	string name;
protected:
	ITestCase* testCase;
public:
	enum TestResult {
		TEST_SUCCESS,
		TEST_FAILURE,
		TEST_CRASH
	};

public:
	UnitTest(string name, ITestCase* testCase);
	UnitTest(int id, string name, ITestCase* testCase);
	UnitTest(int id, string name, test_function_t testFunction);
	UnitTest(string name, test_function_t testCase);

public:
	virtual bool Run();

	virtual ~UnitTest();

private:
	string ConvertResult(TestResult result);
protected:
	virtual string GenerateResultString(TestResult result);
	virtual void PrintResult(TestResult result);

};

