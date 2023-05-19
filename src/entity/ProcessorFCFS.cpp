#include "ProcessorFCFS.h"
#include "../control/Scheduler.h"

Queue<Pair<unsigned int, unsigned int>> ProcessorFCFS::SIGKILL;

ProcessorFCFS::ProcessorFCFS(Scheduler* outScheduler)
	:Processor(outScheduler, FCFS)
{
}

void ProcessorFCFS::AddToKill(Pair<unsigned int, unsigned int> outP)
{
	SIGKILL.enqueue(outP);
}

bool ProcessorFCFS::KillORPH(int PID)
{
	Process* killedProcess = nullptr;

	if (currentProcess != nullptr && currentProcess->GetID() == PID)
	{
		killedProcess = currentProcess;
		currentProcess = nullptr;
		SetStatus(IDLE);
	}
	else
	{
		killedProcess = readyList.RemoveById(PID);
	}

	if (killedProcess == nullptr)
		return false;

	scheduler->TerminateProcess(killedProcess);

	scheduler->IncrementKillCount();

	return true;
}


unsigned ProcessorFCFS::GetTotalReadyTime() const
{
	unsigned totalReadyTime = 0;

	for (int i = 0; i < readyList.GetLength(); i++)
	{
		Process* process = readyList.GetEntry(i + 1);

		if (!process->IsForked())
			totalReadyTime += process->GetTimeInfo().RCT;

	}

	return totalReadyTime;
}

void ProcessorFCFS::SIGKILLHandler()
{
	if (SIGKILL.isEmpty())
		return;

	int timeToKill = SIGKILL.peekFront().first;
	if (timeToKill < this->scheduler->GetCurrentTime())
	{
		SIGKILL.dequeue();
		if (SIGKILL.isEmpty())
			return;
		timeToKill = SIGKILL.peekFront().first;
	}

	if (timeToKill != this->scheduler->GetCurrentTime())
		return;

	int ID_toKill = SIGKILL.peekFront().second;

	KillProcess(ID_toKill);
}

bool ProcessorFCFS::KillProcess(int PID)
{
	Process* killedProcess = nullptr;
	if (currentProcess && *(currentProcess) == PID)
	{
		killedProcess = currentProcess;
		currentProcess = nullptr;
		SetStatus(IDLE);
	}
	else
	{
		killedProcess = readyList.RemoveById(PID);
	}

	if (killedProcess == nullptr)
		return false;

	/// ADDED for stats by Amir
	scheduler->IncrementKillCount();

	SIGKILL.dequeue();
	scheduler->TerminateProcess(killedProcess);
	return true;
}

bool ProcessorFCFS::ExecuteProcess(int CurrentTime)
{
	// i. check if the processor is over heated - OVER HEATING
	if (this->status == STOP)
	{
		overheatCounter--;

		if (overheatCounter <= 0)
		{
			status = IDLE;
		}
		return false;
	}

	// ii. checks if the current process needs IO
	if (currentProcess)
	{
		bool moveFromRun = scheduler->IO_RequestHandler(currentProcess);

		if (moveFromRun)
		{
			currentProcess = nullptr;
			status = IDLE;
		}
	}

	// iii. if the process finished execution, it should be terminated
	if (currentProcess && currentProcess->GetTimeInfo().RCT <= 0)
	{
		scheduler->TerminateProcess(currentProcess);
		currentProcess = nullptr;
		status = IDLE;
	}


	// iV. Migration and schedule next - check if there is no process running
	if (currentProcess == nullptr)
	{

		Process* process = nullptr;

		bool didMigrate = true;
		while (didMigrate)
		{
			if (readyList.IsEmpty())
				return false;

			process = readyList.GetEntry(1);

			// if the process just arrived, make it wait in the ready list
			if (process->GetTimeInfo().AT >= CurrentTime)
				return false;

			readyList.Remove(1);
			didMigrate = scheduler->MigrateFCFS(process);
		}

		currentProcess = process;

		// if the first execution, set the RT
		// the condition where a process must stay at least stay one step before execution allows this
		if (currentProcess->GetTimeInfo().RT == 0)
			currentProcess->SetRT(CurrentTime - currentProcess->GetTimeInfo().AT);

		process->SetStatus(RUN);
		status = BUSY;
		startingTime = CurrentTime;

		return true;
	}

	// V. fork a child if you meet the probability
	scheduler->ForkHandler(currentProcess);

	// Vi. decrement the expected finish time and the RCT by one
	expectedFinishTime--;
	currentProcess->DecrementRCT();

	// VII. manage kill signals
	SIGKILLHandler();

	// VIII. increment the total busy time
	IncrementTotalBusyTime();

	return true;
}

void ProcessorFCFS::AddProcessToList(Process* process)
{
	process->SetCurrentProcessor(this);
	process->SetStatus(RDY);
	TimeInfo timeInfo = process->GetTimeInfo();
	expectedFinishTime += timeInfo.RCT;
	readyList.Insert(readyList.GetLength() + 1, process);
}

Process* ProcessorFCFS::StealProcess()
{
	// if no process to steal exit
	if (readyList.IsEmpty())
		return nullptr;

	// get the first non-forked process


	int i = 1;
	Process* process = readyList.GetEntry(i);

	while (process && process->IsForked())
	{
		i++;
		process = readyList.GetEntry(i);
	}

	// if no non-forked process exit
	if (process == nullptr)
		return nullptr;

	// remove the process from the ready list
	readyList.Remove(i);
	// decrement the expected finish time by the RCT of the process
	expectedFinishTime -= process->GetTimeInfo().RCT;
	// return the process
	return process;
}

void ProcessorFCFS::OverHeat()
{
	// move running process
	if (currentProcess)
	{
		Processor* shortestProcessor = scheduler->GetShortestRDYProcessor();

		if (currentProcess->IsForked())
		{
			scheduler->TerminateProcess(currentProcess);
		}
		else {
			scheduler->Schedule(currentProcess, shortestProcessor);
		}
		currentProcess = nullptr;
	}

	// move ready list processes
	while (!readyList.IsEmpty())
	{
		Process* process = readyList.GetEntry(1);
		readyList.Remove(1);
		Processor* shortestProcessor = scheduler->GetShortestRDYProcessor();
		if (process->IsForked())
		{
			scheduler->TerminateProcess(process);
		}
		else
		{
			scheduler->Schedule(process, shortestProcessor);
		}
	}

	// reset expected finish time
	expectedFinishTime = 0;
}

std::string ProcessorFCFS::ToString()
{
	std::string str = "[FCFS]: " + std::to_string(readyList.GetLength()) + " RDY: ";
	str += readyList.ToString();
	str += "\n";
	return str;
}
