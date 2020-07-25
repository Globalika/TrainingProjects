#include "SimpleTimer.h"

SimpleTimer::SimpleTimer()
{
	start = std::chrono::high_resolution_clock::now();
}

SimpleTimer::~SimpleTimer()
{
	end = std::chrono::high_resolution_clock::now();
	duraction = end - start;
	float result = duraction.count();
	std::cout << "time pass: " << result << " s" << std::endl;
}