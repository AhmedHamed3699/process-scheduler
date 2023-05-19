#include "Processor.h"

Processor::Processor(Scheduler* outScheduler, ProcessorType aType) : scheduler(outScheduler),
status(IDLE), currentProcess(nullptr), totalBusyTime(0), expectedFinishTime(0), startingTime(0), overheatCounter(0)
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

unsigned int Processor::GetTotalBusyTime() const
{
	return totalBusyTime;
}

void Processor::SetHeatingTime(int time)
{
	overheatCounter = time;
}

void Processor::IncrementTotalBusyTime()
{
	if (status == BUSY)
		totalBusyTime++;
}

unsigned int Processor::GetExpectedFinishTime() const
{
	return expectedFinishTime;
}

unsigned int Processor::GetTotalReadyTime() const
{
	if (currentProcess == nullptr)
		return expectedFinishTime;

	return expectedFinishTime - currentProcess->GetTimeInfo().RCT;
}

Processor::~Processor()
{
}
