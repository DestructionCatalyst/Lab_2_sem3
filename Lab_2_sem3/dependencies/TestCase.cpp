#include "TestCase.h"

TestCase::TestCase(function<void()> testFunction):
	ITestCase(), testFunction(testFunction)
{}


void TestCase::Execute()
{
	testFunction();
}