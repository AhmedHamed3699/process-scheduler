#pragma once
#include "Processor.h"
#include "Process.h"
#include "../ds/FCFSList.h"
#include "../data.h"

class ProcessorFCFS : public Processor
{
private:
	FCFSList<Process*> readyList;
	static Queue<Pair<unsigned int, unsigned int>> SIGKILL;			//In each Pair, first is the time and second is the PID

	void SIGKILLHandler();											//it manages how and when process would be killed
	bool KillProcess(int PID);										//responsible for dealing with SIGKILL

public:
	ProcessorFCFS(Scheduler* outScheduler);
	bool ExecuteProcess(int CurrentTime);							//The function responsible for executing a process
	void AddProcessToList(Process* process);						//Adds a Process to the list of a Processor 
	Process* StealProcess();										// Steals a Process from the list of a Processor and returns it
	void OverHeat();												//OverHeating function
	static void AddToKill(Pair<unsigned int, unsigned int> outP);	// adds new kill messages
	bool KillORPH(int PID);											//Function to handle killing the Orphans in the Processor

	std::string ToString();
};

