#pragma once

#include "UnitTest.h"
#include "TimedTestCase.h"

typedef function<void(Timer&)> timed_function;

class TimedTest :
	public UnitTest
{
public:
	TimedTest(int id, string name, timed_function testFunction);
	TimedTest(string name, timed_function testFunction);
protected:
	virtual string GenerateResultString(TestResult result) override;
	virtual void PrintResult(TestResult result) override;

	int GetTestTime();
};

