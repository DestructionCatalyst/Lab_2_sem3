#include "Timer.h"

void Timer::Start()
{
	if (!running)
	{
		//startTime = clock();
		start = system_clock::now();
		running = true;
		
	}	
}

void Timer::Pause()
{
	if (running)
	{
		//clocks += clock() - startTime;
		finish = system_clock::now();
		running = false;
	}
}

double Timer::GetMS()
{
	if (running)
		finish = system_clock::now();

	duration<double> elapsed = finish - start;
	return elapsed.count() * 1000;


	//return clocks;
}

