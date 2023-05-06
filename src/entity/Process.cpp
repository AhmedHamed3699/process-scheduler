#include "Process.h"
#include <string>

Process::Process(int id, unsigned int ioNum, Queue<Pair<unsigned int, unsigned int>>& outIO) :
	PID(id), currentProcessor(nullptr), IONumOfReq(ioNum), descendant(nullptr), status(NEW), IO(outIO), isStolen(false)
{
}

int Process::GetID() const
{
	return PID;
}

Process* Process::GetDescendant() const
{
	return descendant;
}

void Process::SetDescendant(Process* child)
{
	descendant = child;
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
	if (IO.peekFront().first == timeInfo.CT - timeInfo.RCT)
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

std::string Process::ToString()
{
	return std::to_string(PID);
}


