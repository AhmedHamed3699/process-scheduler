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

bool ProcessorSJF::ExecuteProcess(int CurrentTime)
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

void ProcessorSJF::AddProcessToList(Process* process)
{
	process->SetStatus(RDY);
	TimeInfo timeInfo = process->GetTimeInfo();
	expectedFinishTime += timeInfo.RCT;
	readyList.enqueue(process);
}

std::string ProcessorSJF::ToString()
{
	std::string str = "[SJF ]: " + std::to_string(readyList.getSize()) + " RDY: ";
	str += readyList.ToString();
	str += "\n";
	return str;
}
