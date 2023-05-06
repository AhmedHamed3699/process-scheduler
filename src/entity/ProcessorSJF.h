#pragma once
#include "Processor.h"
#include "../ds/PriorityQueue.h"
#include "Process.h"

class ProcessorSJF : public Processor
{
private:
	PriorityQueue<Process*> readyList;

	void IOHandler();				//it manages how the I/O for a process would happen

public:
	ProcessorSJF(Scheduler* outScheduler);
	bool ExecuteProcess(int CurrentTime);		//The function responsible for executing a process
	void AddProcessToList(Process* process);	//Adds a Process to the list of a Processor 
	Process* StealProcess();					// Steals a Process from the list of a Processor and returns it

	std::string ToString();
};

