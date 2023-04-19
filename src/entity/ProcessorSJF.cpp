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

Process* ProcessorSJF::ExecuteProcess(int CurrentTime, int ID)
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

void ProcessorSJF::AddProcessToList(Process* process)
{
	process->SetStatus(RDY);
	readyList.enqueue(process);
}

std::string ProcessorSJF::ToString()
{
	std::string str = "[SJF ]: " + std::to_string(readyList.getSize()) + " RDY: ";
	str += readyList.ToString();
	str += "\n";
	return str;
}
