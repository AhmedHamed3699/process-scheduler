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

	void IOHandler();				//it manages how the I/O for a process would happen
	void WorkStealingHandler();		//it manages how the work stealing between processors would happen
	void MigratonHandler();			//it manages how the migration between processors would happen
public:
	ProcessorRR(Scheduler* outScheduler);
	bool ExecuteProcess(int CurrentTime);	//The function responsible for executing a process
	void AddProcessToList(Process* process);			//Adds a Process to the list of a Processor 

	std::string ToString();
};

