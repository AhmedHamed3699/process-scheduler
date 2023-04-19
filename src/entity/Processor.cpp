#include "Processor.h"

Processor::Processor(Scheduler* outScheduler, ProcessorType aType) : scheduler(outScheduler),
status(IDLE), currentProcess(nullptr), totalBusyTime(0), expectedFinishTime(0), startingTime(0)
{
}

ProcessorStatus Processor::GetStatus() const
{
	return status;
}

void Processor::SetStatus(ProcessorStatus outStatus)
{
	status = outStatus;
}

Process* Processor::GetCurrentProcess() const
{
	return currentProcess;
}

void Processor::SetCurrentProcess(Process* outProcess)
{
	currentProcess = outProcess;
}

unsigned int Processor::GetTotalBusyTime() const
{
	return totalBusyTime;
}

void Processor::SetTotalBusyTime(unsigned int time)
{
	totalBusyTime = time;
}

unsigned int Processor::GetExpectedFinishTime() const
{
	return expectedFinishTime;
}

void Processor::SetExpectedFinishTime(unsigned int time)
{
	expectedFinishTime = time;
}

Processor::~Processor()
{
}
