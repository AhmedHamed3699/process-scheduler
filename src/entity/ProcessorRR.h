#pragma once
#include "Processor.h"
#include "Process.h"
#include "../ds/Queue.h"



class ProcessorRR : public Processor
{
private:
	Queue<Process*> readyList;			//the list of processes that are ready to be executed
	const unsigned int RR_TIME_SLICE;	//the quantum time of the processor
	unsigned int quantumCounter;		//the counter that counts the quantum time

	void IOHandler();					//it manages how the I/O for a process would happen
public:
	ProcessorRR(Scheduler* outScheduler);
	bool ExecuteProcess(int CurrentTime);				//The function responsible for executing a process
	void AddProcessToList(Process* process);			//Adds a Process to the list of a Processor
	Process* StealProcess();							// Steals a Process from the list of a Processor and returns it
	void OverHeat();									//OverHeating function

	std::string ToString();
};

