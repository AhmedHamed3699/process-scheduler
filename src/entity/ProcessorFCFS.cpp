#include "ProcessorFCFS.h"
#include "../control/Scheduler.h"

Queue<Pair<unsigned int, unsigned int>> ProcessorFCFS::SIGKILL;

ProcessorFCFS::ProcessorFCFS(Scheduler* outScheduler)
	:Processor(outScheduler, FCFS)
{
}

bool ProcessorFCFS::MigratonHandler(int currentTime)
{
	SimulationParameters sP = scheduler->GetSimulationParameters();

	while (!readyList.IsEmpty())
	{
		//Get the first process in the ready list and calculate its waiting time
		Process* process = readyList.GetEntry(1);
		TimeInfo timeInfo = process->GetTimeInfo();
		int waitingTime = (currentTime - timeInfo.AT) - (timeInfo.CT - timeInfo.RCT);

		if (waitingTime > sP.MAX_WAITING_TIME)
		{
			//migrate the process to a RR processor
			bool isSuccessful = scheduler->ScheduleNextRR(process);

			//if the migration failed due to not having any RR processors
			if (!isSuccessful)
				return false;

			//if the process migrated, remove it from the ready list
			readyList.Remove(1);
		}
		else
		{
			return false;
		}
	}

	//return true if all the processes in the ready list migrated and the ready list became empty
	return true;
}

void ProcessorFCFS::AddToKill(Pair<unsigned int, unsigned int> outP)
{
	SIGKILL.enqueue(outP);
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
	else if (timeToKill != this->scheduler->GetCurrentTime())
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

	SIGKILL.dequeue();
	scheduler->TerminateProcess(killedProcess);
	return true;
}

bool ProcessorFCFS::ExecuteProcess(int CurrentTime)
{
	// we need to re-order callings, so it makes more sense

	SIGKILLHandler();

	if (currentProcess)
	{
		bool moveFromRun = scheduler->IO_RequestHandler(currentProcess);

		if (moveFromRun)
		{
			currentProcess = nullptr;
			status = IDLE;
			//return true; // see if you don't want to do IO and running at the same time stamp
		}
	}

	//check if there is no process running
	if (currentProcess == nullptr)
	{
		if (readyList.IsEmpty())
			return false;

		//the function would return true if the readyList is empty and false if the migration didn't continue
		bool migratedOrNot = MigratonHandler(CurrentTime);

		if (migratedOrNot)
			return false;

		//get the first process and remove it from the readyList
		Process* process = readyList.GetEntry(1);

		// if the process just arrived, make it wait in the ready list
		if (process->GetTimeInfo().AT >= CurrentTime)
			return false;

		readyList.Remove(1);
		currentProcess = process;

		process->SetStatus(RUN);
		status = BUSY;
		startingTime = CurrentTime;

		return true;
	}

	// fork a child if you meet the probability
	scheduler->ForkHandler(currentProcess);

	//decrement the expected finish time and the RCT by one
	expectedFinishTime--;
	currentProcess->DecrementRCT();

	// increment the total busy time
	IncrementTotalBusyTime();

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

std::string ProcessorFCFS::ToString()
{
	std::string str = "[FCFS]: " + std::to_string(readyList.GetLength()) + " RDY: ";
	str += readyList.ToString();
	str += "\n";
	return str;
}
