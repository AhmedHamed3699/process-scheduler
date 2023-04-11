#pragma once
///=////////////////////////////////////////=///
/// Clock Class: Stores and updates the time ///
///=////////////////////////////////////////=///
class Clock
{
private:
	unsigned int time;
public:
	Clock();
	unsigned int GetCurrentTime() const;
	void Reset();
	void Step();
};