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

void ProcessorFCFS::KillProcessHandler()
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
	return nullptr;
}

void ProcessorFCFS::AddProcessToList(Process* process)
{
	readyList.Insert(readyList.GetLength() + 1, process);
}

void ProcessorFCFS::Print()
{
	std::cout << "[FCFS]: " << readyList.GetLength() << " RDY: ";
	readyList.Print();
	std::cout << std::endl;
}
