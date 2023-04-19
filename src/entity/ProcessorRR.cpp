#include "ProcessorRR.h"
#include <string>

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

Process* ProcessorRR::ExecuteProcess(int CurrentTime, int ID)
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

std::string ProcessorRR::ToString()
{
	std::string str = "[RR ]: " + std::to_string(readyList.getSize()) + " RDY: ";
	str += readyList.ToString();
	str += "\n";
	return str;
}
