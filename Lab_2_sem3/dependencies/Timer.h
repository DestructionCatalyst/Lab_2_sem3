#pragma once
//#include <ctime>
#include <chrono>


using namespace std::chrono;

class Timer
{
private:
	//clock_t startTime = 0;
	//clock_t clocks = 0;
	bool running = false;
	system_clock::time_point start;
	system_clock::time_point finish;
public:
	void Start();
	void Pause();
	double GetMS();
};

