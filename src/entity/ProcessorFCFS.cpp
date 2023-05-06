#include "ProcessorFCFS.h"
#include "../control/Scheduler.h"

Queue<Pair<unsigned int, unsigned int>> ProcessorFCFS::SIGKILL;

void ProcessorFCFS::IOHandler()
{
}

void ProcessorFCFS::MigratonHandler()
{
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
	if(currentProcess && *(currentProcess) == PID)
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

void ProcessorFCFS::ForkHandler()
{
}

ProcessorFCFS::ProcessorFCFS(Scheduler* outScheduler)
	:Processor(outScheduler, FCFS)
{
}

bool ProcessorFCFS::ExecuteProcess(int CurrentTime)
{

	SIGKILLHandler();

	//check if there is no process running
	if (currentProcess == nullptr)
	{
		if (readyList.IsEmpty())
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

	//TODO: manage IO and other things like forking, migration etc...

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
	if (readyList.IsEmpty())
		return nullptr;
	Process* process = readyList.GetEntry(1);
	readyList.Remove(1);
	expectedFinishTime -= process->GetTimeInfo().RCT;
	return process;
}

std::string ProcessorFCFS::ToString()
{
	std::string str = "[FCFS]: " + std::to_string(readyList.GetLength()) + " RDY: ";
	str += readyList.ToString();
	str += "\n";
	return str;
}
