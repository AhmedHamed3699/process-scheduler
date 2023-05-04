#include "ProcessorRR.h"
#include <string>
#include "../control/scheduler.h"

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
	:Processor(outScheduler, RR), RR_TIME_SLICE(this->scheduler->GetSimulationParameters().RR_TIME_SLICE)
{
	quantumCounter = this->scheduler->GetSimulationParameters().RR_TIME_SLICE;
}

bool ProcessorRR::ExecuteProcess(int CurrentTime)
{
	////TODO: remove this later
	//if (readyList.isEmpty())
	//	return false;

	//Process* process = readyList.peekFront();
	//if (process->GetTimeInfo().AT == CurrentTime)
	//	return false;

	//readyList.dequeue();
	//currentProcess = process;
	//process->SetStatus(RUN);
	//SetStatus(BUSY);

	//TimeInfo timeInfo = process->GetTimeInfo();
	//timeInfo.RT = CurrentTime - timeInfo.AT;

	//process->SetTimeInfo(timeInfo);

	//return true;
	// Check if there is a running process 
	if (this->currentProcess == nullptr)
	{
		// schedule next process, unless there is no process in the ready list
		if (readyList.isEmpty())
			return false;

		Process* process = readyList.peekFront();
		readyList.dequeue();
		currentProcess = process;
		process->SetStatus(RUN);
		SetStatus(BUSY);
		return true;
	}

	// Check if the process is finished
	if (currentProcess->GetTimeInfo().RCT == 0)
	{
		// Set the process as finished
		currentProcess->SetStatus(TRM);
		scheduler->TerminateProcess(currentProcess);
		currentProcess = nullptr;
		SetStatus(IDLE);
		return true;
	}

	// if quantum is finished, add the process to the ready list
	if (quantumCounter == 0) // add here the quantum counter
	{
		readyList.enqueue(currentProcess);
		currentProcess->SetStatus(RDY);
		currentProcess = nullptr;
		SetStatus(IDLE);
		quantumCounter = RR_TIME_SLICE;
		return true;
	}

	// execute the process
	currentProcess->DecrementRCT(); // decrement the RCT

	// decrement the quantum counter
	quantumCounter--;

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
