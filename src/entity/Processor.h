#pragma once
///=////////////////////////////////////////////=///
///  Processor Class: runs and stores processes  ///
/// Created By scheduler maintained by scheduler ///
///=////////////////////////////////////////////=///
#include "../control/Scheduler.h"
#include "Process.h"
#include "../data.h"

class Processor
{
protected:
	Scheduler* scheduler;
	ProcessorStatus status;
	Process* currentProcess;
	unsigned int totalBusyTime;
	unsigned int expectedFinishTime;

	virtual void IOHandler() = 0;
	virtual void WorkStealingHandler() = 0;
public:
	Processor(Scheduler* outScheduler);
	virtual ProcessorStatus GetStatus() const;
	virtual void SetStatus(ProcessorStatus outStatus);
	virtual Process* GetCurrentProcess() const;
	virtual void SetCurrentProcess(Process* outProcess);
	virtual unsigned int GetTotalBusyTime() const;
	virtual void SetTotalBusyTime(unsigned int time);
	virtual unsigned int GetExpectedFinishTime() const;
	virtual void SetExpectedFinishTime(unsigned int time);

	virtual Process* ExecuteProcess() = 0;
	virtual void AddProcessToList(Process process) = 0;

	~Processor();
};

