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
	//TODO: remove this later
	if (readyList.getSize() == 0)
	{
		return nullptr;
	}
	Process* process = readyList.peekFront();
	readyList.dequeue();
	currentProcess = process;


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
