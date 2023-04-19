#pragma once
///=////////////////////////////////////////////=///
///  Processor Class: runs and stores processes  ///
/// Created By scheduler maintained by scheduler ///
///=////////////////////////////////////////////=///
#include "Process.h"
#include "../data.h"
#include <string>

// Forward class declaration
class Scheduler;

class Processor
{
protected:
	Scheduler* scheduler;				//Pointer to Scheduler
	ProcessorStatus status;				//current state of the Processor
	Process* currentProcess;			//the process being executed right now by the processor
	unsigned int totalBusyTime;			//the total time the processor was busy (executing a process)
	unsigned int expectedFinishTime;	//expected finish time of the current process
	unsigned int startingTime;			//the time at which the processor started executing the current process

	virtual void IOHandler() = 0;				//it manages how the I/O for a process would happen
	virtual void WorkStealingHandler() = 0;		//it manages how the work stealing between processors would happen
public:
	Processor(Scheduler* outScheduler, ProcessorType aType);
	virtual ~Processor();

	//Setters and Getters for the data members
	virtual ProcessorStatus GetStatus() const;
	virtual void SetStatus(ProcessorStatus outStatus);
	virtual Process* GetCurrentProcess() const;
	virtual void SetCurrentProcess(Process* outProcess);
	virtual unsigned int GetTotalBusyTime() const;
	virtual void SetTotalBusyTime(unsigned int time);
	virtual unsigned int GetExpectedFinishTime() const;
	virtual void SetExpectedFinishTime(unsigned int time);

	virtual bool ExecuteProcess(int CurrentTime, int ID = -1) = 0;	//The function responsible for executing a process
	virtual void AddProcessToList(Process* process) = 0;			//Adds a Process to the list of a Processor 

	virtual std::string ToString() = 0;
};

