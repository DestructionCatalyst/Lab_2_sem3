#include "TimedTest.h"

#include <iostream>
#define ECHO_FOR_GRAPH

TimedTest::TimedTest(int id, string name, timed_function testFunction) :
	UnitTest(id, name, new TimedTestCase(testFunction))
{}

TimedTest::TimedTest(string name, timed_function testFunction) :
	UnitTest(rand(), name, new TimedTestCase(testFunction))
{}

string TimedTest::GenerateResultString(TestResult result)
{
	return (std::stringstream() 
		<< UnitTest::GenerateResultString(result)
		<< " Time: " << GetTestTime() / 1000. << " seconds" ).str(); 
}

void TimedTest::PrintResult(TestResult result)
{
	#ifndef ECHO_FOR_GRAPH
	std::cout << GenerateResultString(result) << std::endl;
	#endif // ECHO_FOR_GRAPH
	
}

int TimedTest::GetTestTime()
{

	//std::cout << dynamic_cast<TimedTestCase*>(testCase)->GetTestTime() << std::endl;
	return dynamic_cast<TimedTestCase*>(testCase)->GetTestTime();
}