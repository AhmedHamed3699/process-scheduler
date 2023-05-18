#include "ProcessorRR.h"
#include <string>
#include "../control/scheduler.h"

void ProcessorRR::IOHandler()
{
}

ProcessorRR::ProcessorRR(Scheduler* outScheduler)
	:Processor(outScheduler, RR), RR_TIME_SLICE(this->scheduler->GetSimulationParameters().RR_TIME_SLICE)
{
	quantumCounter = this->scheduler->GetSimulationParameters().RR_TIME_SLICE;
}

bool ProcessorRR::ExecuteProcess(int CurrentTime)
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

	/// 1. if the process is finished, terminate it
	// Check if the process is finished
	if (currentProcess && currentProcess->GetTimeInfo().RCT <= 0)
	{
		// Set the process as finished
		scheduler->TerminateProcess(currentProcess);
		currentProcess = nullptr;
		SetStatus(IDLE);
		quantumCounter = RR_TIME_SLICE;
	}

	/// 2. checks if the current process needs IO
	if (currentProcess)
	{
		bool moveFromRun = scheduler->IO_RequestHandler(currentProcess);

		if (moveFromRun)
		{
			currentProcess = nullptr;
			status = IDLE;
		}
	}

	/// 3. if no running process, schedule next process
	if (this->currentProcess == nullptr)
	{
		Process* process = nullptr;

		bool didMigrate = true; // checks if the current process needs migration
		while (didMigrate)
		{
			if (readyList.isEmpty())
				return false;

			process = readyList.peekFront();

			// if the process just arrived, make it wait in the ready list
			if (process->GetTimeInfo().AT >= CurrentTime)
				return false;

			readyList.dequeue();
			didMigrate = scheduler->MigrateRR(process);
		}

		currentProcess = process;

		// if the first execution, set the RT
		// the condition where a process must stay at least stay one step before execution allows this
		if (currentProcess->GetTimeInfo().RT == 0)
			currentProcess->SetRT(CurrentTime - currentProcess->GetTimeInfo().AT);

		process->SetStatus(RUN);
		SetStatus(BUSY);
		return true;
	}

	/// 4. if the process is not finished, check if the quantum is finished
	// if quantum is finished, add the process to the ready list
	if (quantumCounter == 0) // add here the quantum counter
	{
		//checks if didn't migrate so it can go back to the readylist
		bool didMigrate = scheduler->MigrateRR(currentProcess);

		if (!didMigrate)
			readyList.enqueue(currentProcess);
		currentProcess->SetStatus(RDY);
		currentProcess = nullptr;
		SetStatus(IDLE);
		quantumCounter = RR_TIME_SLICE;
		return true;
	}

	/// 5. if there is a running process, execute it
	// execute the process
	currentProcess->DecrementRCT(); // decrement the RCT

	// decrement the quantum counter
	quantumCounter--;

	// decrement the expected finish time of the processor by one
	expectedFinishTime--;

	// increment the total busy time
	IncrementTotalBusyTime();

	return true;
}

void ProcessorRR::AddProcessToList(Process* process)
{
	process->SetCurrentProcessor(this);
	process->SetStatus(RDY);
	TimeInfo timeInfo = process->GetTimeInfo();
	expectedFinishTime += timeInfo.RCT;
	readyList.enqueue(process);
}

Process* ProcessorRR::StealProcess()
{
	if (readyList.isEmpty())
		return nullptr;
	Process* process = readyList.peekFront();
	expectedFinishTime -= process->GetTimeInfo().RCT;
	readyList.dequeue();
	return process;
}

void ProcessorRR::OverHeat()
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

std::string ProcessorRR::ToString()
{
	std::string str = "[RR ]: " + std::to_string(readyList.getSize()) + " RDY: ";
	str += readyList.ToString();
	str += "\n";
	return str;
}
