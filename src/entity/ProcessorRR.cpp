#include "ProcessorRR.h"

void ProcessorRR::IOHandler()
{
}

void ProcessorRR::WorkStealingHandler()
{
}

void ProcessorRR::MigratonHandler()
{
}

ProcessorRR::ProcessorRR(Scheduler* outScheduler)
	:Processor(outScheduler, RR)
{
}

Process* ProcessorRR::ExecuteProcess()
{
	return nullptr;
}

void ProcessorRR::AddProcessToList(Process* process)
{
	readyList.enqueue(process);
}
