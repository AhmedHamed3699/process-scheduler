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
	/// ////////////////////////////////// ///
	///			  Data Members		   ///
	/// ////////////////////////////////// ///
	Scheduler* scheduler;				//Pointer to Scheduler
	ProcessorStatus status;				//current state of the Processor
	Process* currentProcess;			//the process being executed right now by the processor

	/// stats data members
	unsigned int totalBusyTime;			//the total time the processor was busy (executing a process)
	unsigned int expectedFinishTime;	//expected finish time of the current process
	unsigned int startingTime;			//the time at which the processor started executing the current process
	int overheatCounter;				//counts the time the processor will be overheated for

public:
	/// ////////////////////////////////// ///
	///	     Constructors & Destructor	   ///
	/// ////////////////////////////////// ///
	Processor(Scheduler* outScheduler, ProcessorType aType);
	virtual ~Processor();

	/// ////////////////////////////////// ///
	/// 		 Processor Interface	   ///
	/// ////////////////////////////////// ///
	virtual ProcessorStatus GetStatus() const;
	virtual void SetStatus(ProcessorStatus outStatus);
	virtual Process* GetCurrentProcess() const;
	virtual unsigned int GetTotalBusyTime() const;
	virtual void SetHeatingTime(int time);
	// increments total busy time by 1 if the processor is busy
	virtual void IncrementTotalBusyTime();
	// Gets the time at which the processor will finish executing all processes
	virtual unsigned int GetExpectedFinishTime() const;
	// Gets the total RCT of the ready processes
	virtual unsigned int GetTotalReadyTime() const;
	//The function responsible for executing a process
	virtual bool ExecuteProcess(int CurrentTime) = 0;
	//Adds a Process to the list of a Processor
	virtual void AddProcessToList(Process* process) = 0;

	/// Scheduler Utility Functions
	// Steals a Process from the list of a Processor and returns it
	virtual Process* StealProcess() = 0;
	// OverHeat the processor for a certain amount of time
	virtual void OverHeat() = 0;

	// returns a string representation of the processor
	virtual std::string ToString() = 0;
};

