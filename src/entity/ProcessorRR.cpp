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
	//TODO: remove this later
	if (readyList.getSize() == 0)
	{
		return nullptr;
	}
	Process* process = readyList.peekFront();
	readyList.dequeue();
	currentProcess = process;
	process->SetStatus(RUN);


	return nullptr;
}

void ProcessorRR::AddProcessToList(Process* process)
{
	process->SetStatus(RDY);
	readyList.enqueue(process);
}

void ProcessorRR::Print()
{
	std::cout << "[ RR ]: " << readyList.getSize() << " RDY: ";
	readyList.Print();
	std::cout << std::endl;
}
