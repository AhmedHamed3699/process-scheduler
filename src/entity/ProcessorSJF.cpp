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

Process* ProcessorSJF::ExecuteProcess(int CurrentTime)
{
	//TODO: remove this later
	if (readyList.isEmpty())
	{
		return nullptr;
	}
	Process* process = readyList.peekFront();
	if(process->GetTimeInfo().AT == CurrentTime)
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

void ProcessorSJF::AddProcessToList(Process* process)
{
	process->SetStatus(RDY);
	readyList.enqueue(process);
}

void ProcessorSJF::Print()
{
	std::cout << "[SJF ]: " << readyList.getSize() << " RDY: ";
	readyList.Print();
	std::cout << std::endl;
}
