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
}
