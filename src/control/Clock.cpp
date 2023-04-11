#include "Clock.h"

Clock::Clock() : time(0) {}

unsigned int Clock::GetCurrentTime() const
{
	return time;
}

void Clock::Reset()
{
	time = 0;
}

void Clock::Step()
{
	time++;
}