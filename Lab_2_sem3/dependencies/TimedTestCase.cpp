#include "TimedTestCase.h"

#include <iostream>

TimedTestCase::TimedTestCase(function<void(Timer&)> testFunction):
	ITestCase(), testFunction(testFunction), timer()
{}

void TimedTestCase::Execute()
{
	testFunction(timer);
}

int TimedTestCase::GetTestTime()
{
	//std::cout << timer.GetMS() << std::endl;
	return timer.GetMS();
}