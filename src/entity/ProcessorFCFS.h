#pragma once
#include "Processor.h"
#include "Process.h"
#include "../ds/FCFSList.h"
#include "../data.h"

class ProcessorFCFS : public Processor
{
private:
	FCFSList<Process*> readyList;

	void IOHandler();						//it manages how the I/O for a process would happen
	void WorkStealingHandler();				//it manages how the work stealing between processors would happen
	void MigratonHandler();					//it manages how the migration between processors would happen
	void ForkHandler();						//Handles how Forking would be done
	bool KillProcessHandler(int PID);		//responsible for dealing with SIGKILL and Orphans

public:
	ProcessorFCFS(Scheduler* outScheduler);
	Process* ExecuteProcess(int CurrentTime);				//The function responsible for executing a process
	void AddProcessToList(Process* process);//Adds a Process to the list of a Processor 
	std::string ToString();
};

