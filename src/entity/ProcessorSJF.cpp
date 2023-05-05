#include "ProcessorSJF.h"
#include "../control/Scheduler.h"

void ProcessorSJF::IOHandler()
{
}

ProcessorSJF::ProcessorSJF(Scheduler* outScheduler)
	:Processor(outScheduler, SJF)
{
}

bool ProcessorSJF::ExecuteProcess(int CurrentTime)
{
	if (currentProcess == nullptr)
	{
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

	//decrement the expected finish time and the RCT by one
	expectedFinishTime--;
	currentProcess->DecrementRCT();
	
	//if the process finished execution, it should be terminated
	if (currentProcess->GetTimeInfo().RCT <= 0)
	{
		scheduler->TerminateProcess(currentProcess);
		currentProcess = nullptr;
		status = IDLE;
		return true;
	}

	return true;
}

void ProcessorSJF::AddProcessToList(Process* process)
{
	process->SetStatus(RDY);
	TimeInfo timeInfo = process->GetTimeInfo();
	expectedFinishTime += timeInfo.RCT;
	readyList.enqueue(process);
}

Process* ProcessorSJF::StealProcess()
{
	if (readyList.isEmpty())
		return nullptr;
	Process* process = readyList.peekFront();
	expectedFinishTime -= process->GetTimeInfo().RCT;
	readyList.dequeue();
	return process;
}

std::string ProcessorSJF::ToString()
{
	std::string str = "[SJF ]: " + std::to_string(readyList.getSize()) + " RDY: ";
	str += readyList.ToString();
	str += "\n";
	return str;
}
