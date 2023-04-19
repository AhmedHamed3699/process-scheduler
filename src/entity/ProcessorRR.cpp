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

bool ProcessorRR::ExecuteProcess(int CurrentTime)
{
	//TODO: remove this later
	if (readyList.isEmpty())
		return false;

	Process* process = readyList.peekFront();
	if (process->GetTimeInfo().AT == CurrentTime)
		return false;

	readyList.dequeue();
	currentProcess = process;
	process->SetStatus(RUN);
	SetStatus(BUSY);

	TimeInfo timeInfo = process->GetTimeInfo();
	timeInfo.RT = CurrentTime - timeInfo.AT;

	process->SetTimeInfo(timeInfo);

	return true;
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
