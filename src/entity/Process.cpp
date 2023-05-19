#include "Process.h"
#include <string>

Process::Process(int id, Queue<Pair<unsigned int, unsigned int>>& outIO) :
	PID(id), currentProcessor(nullptr), firstChild(nullptr), secondChild(nullptr), status(NEW), 
	IO(outIO), isStolen(false), isForked(false), numberOfForking(0)
{
}

int Process::GetID() const
{
	return PID;
}

Process* Process::GetFirstChild() const
{
	return firstChild;
}

Process* Process::GetSecondChild() const
{
	return secondChild;
}

void Process::SetChild(Process* child)
{
	if (numberOfForking >= 2)
		return;

	if (numberOfForking == 0)
		firstChild = child;
	else
		secondChild = child;

	numberOfForking++;
}

Processor* Process::GetCurrentProcessor() const
{
	return currentProcessor;
}

void Process::SetCurrentProcessor(Processor* CP)
{
	currentProcessor = CP;
}

TimeInfo Process::GetTimeInfo() const
{
	return timeInfo;
}

void Process::SetTimeInfo(TimeInfo tI)
{
	timeInfo = tI;
}

void Process::DecrementRCT()
{
	timeInfo.RCT--;
}

void Process::SetTT(unsigned int time)
{
	timeInfo.TT = time;
}

void Process::SetRT(unsigned int time)
{
	timeInfo.RT = time;
}

void Process::CalcTRT()
{
	timeInfo.TRT = timeInfo.TT - timeInfo.AT;
}

void Process::CalcWT()
{
	timeInfo.WT = timeInfo.TRT - (timeInfo.CT - timeInfo.RCT);
}

ProcessStatus Process::GetStatus() const
{
	return status;
}

void Process::SetStatus(ProcessStatus outStatus)
{
	status = outStatus;
}

Pair<unsigned int, unsigned int> Process::GetTopIOPair()
{
	if (!IO.isEmpty())
	{
		Pair<unsigned int, unsigned int> topP = IO.peekFront();
		IO.dequeue();
		return topP;
	}
	else
	{
		Pair<unsigned int, unsigned int> emptyP(0, 0);
		return emptyP;
	}
}

bool Process::operator== (int id)
{
	return (PID == id);
}

bool Process::operator< (Process* p)
{
	return (timeInfo.RCT < p->timeInfo.RCT);
}

bool Process::NeedIO(int currentTime) const
{
	if (IO.isEmpty())
		return false;

	if (IO.peekFront().first == timeInfo.CT - timeInfo.RCT + 1)
		return true;
	return false;
}

bool Process::IsStolen() const
{
	return isStolen;
}

void Process::SetStolen(bool isStolen)
{
	this->isStolen = isStolen;
}

bool Process::IsForked() const
{
	return isForked;
}

void Process::SetForked(bool isForked)
{
	this->isForked = isForked;
}

bool Process::CanFork() const
{
	return (numberOfForking < 2);
}

void Process::killchildren()
{
	firstChild = nullptr;
	secondChild = nullptr;
}

std::string Process::ToString()
{
	return std::to_string(PID);
}


