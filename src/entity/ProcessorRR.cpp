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

Process* ProcessorRR::ExecuteProcess(int CurrentTime)
{
	//TODO: remove this later
	if (readyList.isEmpty())
	{
		return nullptr;
	}
	Process* process = readyList.peekFront();
	if (process->GetTimeInfo().AT == CurrentTime)
		return nullptr;

	readyList.dequeue();
	currentProcess = process;
	process->SetStatus(RUN);
	SetStatus(BUSY);

	TimeInfo timeInfo = process->GetTimeInfo();
	timeInfo.RT = CurrentTime - timeInfo.AT;

	process->SetTimeInfo(timeInfo);

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
