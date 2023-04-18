#include "ProcessorFCFS.h"

void ProcessorFCFS::IOHandler()
{
}

void ProcessorFCFS::WorkStealingHandler()
{
}

void ProcessorFCFS::MigratonHandler()
{
}

bool ProcessorFCFS::KillProcessHandler(int PID)
{
	
}

void ProcessorFCFS::ForkHandler()
{
}

ProcessorFCFS::ProcessorFCFS(Scheduler* outScheduler)
	:Processor(outScheduler, FCFS)
{
}

Process* ProcessorFCFS::ExecuteProcess()
{
	//TODO: remove this later
	if (readyList.IsEmpty())
	{
		return nullptr;
	}
	Process* process = readyList.GetEntry(1);
	readyList.Remove(1);
	currentProcess = process;
	process->SetStatus(RUN);

	return nullptr;
}

void ProcessorFCFS::AddProcessToList(Process* process)
{
	process->SetStatus(RDY);
	readyList.Insert(readyList.GetLength() + 1, process);
}

void ProcessorFCFS::Print()
{
	std::cout << "[FCFS]: " << readyList.GetLength() << " RDY: ";
	readyList.Print();
	std::cout << std::endl;
}
