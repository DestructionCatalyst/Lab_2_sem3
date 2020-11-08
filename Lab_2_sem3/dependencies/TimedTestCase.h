#pragma once

#include <functional>

#include "ITestCase.h"
#include "Timer.h"

using std::function;

class TimedTestCase: public ITestCase
{
private:
	function<void(Timer&)> testFunction;
	Timer timer;
public:
	TimedTestCase(function<void(Timer&)> testFunction);
	void Execute() override;
	int GetTestTime();
};

