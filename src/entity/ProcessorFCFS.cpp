#include "ProcessorFCFS.h"
#include "../control/Scheduler.h"

void ProcessorFCFS::IOHandler()
{
}

void ProcessorFCFS::WorkStealingHandler()
{
}

void ProcessorFCFS::MigratonHandler()
{
}

bool ProcessorFCFS::KillProcess(int PID)
{
	Process* killedProcess = readyList.RemoveById(PID);
	if (killedProcess == nullptr)
		return false;
	if (killedProcess == GetCurrentProcess())
	{
		SetCurrentProcess(nullptr);
		SetStatus(IDLE);
	}
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
	//TODO: when implementing the new ExecuteProcess (for phase 2) don't forget to uncomment this line
	//expectedFinishTime--;

	//TODO: remove this later

	if (readyList.IsEmpty())
		return false;

	Process* process = readyList.GetEntry(1);
	if (process->GetTimeInfo().AT == CurrentTime)
		return false;

	readyList.Remove(1);
	currentProcess = process;
	process->SetStatus(RUN);
	SetStatus(BUSY);

	TimeInfo timeInfo = process->GetTimeInfo();
	timeInfo.RT = CurrentTime - timeInfo.AT;

	process->SetTimeInfo(timeInfo);

	return true;
}

void ProcessorFCFS::AddProcessToList(Process* process)
{
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
