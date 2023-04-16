#include "ProcessorSJF.h"

void ProcessorSJF::IOHandler()
{
}

void ProcessorSJF::WorkStealingHandler()
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
