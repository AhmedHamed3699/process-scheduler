#pragma once
#include "Processor.h"
#include "../ds/PriorityQueue.h"
#include "Process.h"

class ProcessorSJF : public Processor
{
private:
	PriorityQueue<Process*> readyList;

	void IOHandler();				//it manages how the I/O for a process would happen
	void WorkStealingHandler();		//it manages how the work stealing between processors would happen

public:
	ProcessorSJF(Scheduler* outScheduler);
	Process* ExecuteProcess(int CurrentTime, int ID = -1);	//The function responsible for executing a process
	void AddProcessToList(Process* process);				//Adds a Process to the list of a Processor 

	std::string ToString();
};

