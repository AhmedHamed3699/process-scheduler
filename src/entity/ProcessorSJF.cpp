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
	// we need to re-order callings, so it makes more sense

	// check if the processor is over heated - OVER HEATING
	if (this->status == STOP)
	{
		overheatCounter--;

		if (overheatCounter <= 0)
		{
			status = IDLE;
		}
		return false;
	}
	if (currentProcess)
	{
		bool moveFromRun = scheduler->IO_RequestHandler(currentProcess);

		if (moveFromRun)
		{
			currentProcess = nullptr;
			status = IDLE;
		}
	}

	// if the process finished execution, it should be terminated
	if (currentProcess && currentProcess->GetTimeInfo().RCT <= 0)
	{
		scheduler->TerminateProcess(currentProcess);
		currentProcess = nullptr;
		SetStatus(IDLE);
	}


	// check if there is no process running
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

		// if the first execution, set the RT
		// the condition where a process must stay at least stay one step before execution allows this
		if (currentProcess->GetTimeInfo().RT == 0)
			currentProcess->SetRT(CurrentTime - currentProcess->GetTimeInfo().AT);

		return true;

	}

	//decrement the expected finish time and the RCT by one
	expectedFinishTime--;
	currentProcess->DecrementRCT();

	// increment the total busy time
	IncrementTotalBusyTime();

	return true;
}

void ProcessorSJF::AddProcessToList(Process* process)
{
	process->SetCurrentProcessor(this);
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

void ProcessorSJF::OverHeat()
{
	// move running process
	if (currentProcess)
	{
		Processor* shortestProcessor = scheduler->GetShortestRDYProcessor();
		scheduler->Schedule(currentProcess, shortestProcessor);
		currentProcess = nullptr;
	}

	// move ready list processes
	while (!readyList.isEmpty())
	{
		Process* process = readyList.peekFront();
		readyList.dequeue();
		Processor* shortestProcessor = scheduler->GetShortestRDYProcessor();
		scheduler->Schedule(process, shortestProcessor);
	}

	// reset expected finish time
	expectedFinishTime = 0;
}

std::string ProcessorSJF::ToString()
{
	std::string str = "[SJF ]: " + std::to_string(readyList.getSize()) + " RDY: ";
	str += readyList.ToString();
	str += "\n";
	return str;
}
