#include "ProcessorSJF.h"

void ProcessorSJF::IOHandler()
{
}

void ProcessorSJF::WorkStealingHandler()
{
}

ProcessorSJF::ProcessorSJF(Scheduler* outScheduler)
	:Processor(outScheduler, SJF)
{
}

Process* ProcessorSJF::ExecuteProcess()
{
	return nullptr;
}

void ProcessorSJF::AddProcessToList(Process* process)
{
	readyList.enqueue(process);
}
