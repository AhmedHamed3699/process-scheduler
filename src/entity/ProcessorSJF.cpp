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

void ProcessorSJF::Print()
{
	std::cout << "[SJF ]: " << readyList.getSize() << " RDY: ";
	readyList.Print();
	std::cout << std::endl;
}
