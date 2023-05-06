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
	void MigratonHandler();					//it manages how the migration between processors would happen
	void ForkHandler();						//Handles how Forking would be done

public:
	ProcessorFCFS(Scheduler* outScheduler);
	bool ExecuteProcess(int CurrentTime);		//The function responsible for executing a process
	void AddProcessToList(Process* process);	//Adds a Process to the list of a Processor 
	Process* StealProcess();					// Steals a Process from the list of a Processor and returns it
	bool KillProcess(int PID);		//responsible for dealing with SIGKILL and Orphans

	std::string ToString();
};

