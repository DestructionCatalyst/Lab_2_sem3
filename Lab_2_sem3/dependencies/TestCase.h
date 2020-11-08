#pragma once

#include <functional>

#include "ITestCase.h"

using std::function;

class TestCase :
	public ITestCase
{
private:
	function<void()> testFunction;
public:
	TestCase(function<void()> testFunction);
	void Execute() override;
};

