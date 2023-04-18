#include "Process.h"

Process::Process(int id, unsigned int ioNum) : PID(id), IONumOfReq(ioNum), descendant(nullptr), status(NEW)
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

TimeInfo Process::GetTimeInfo() const
{
	return timeInfo;
}

void Process::SetTimeInfo(TimeInfo tI)
{
	timeInfo = tI;
}

unsigned int Process::GetIONumOfReq() const
{
	return IONumOfReq;
}

void Process::SetIONumOfReq(unsigned int ioNum)
{
	IONumOfReq = ioNum;
}

ProcessStatus Process::GetStatus() const
{
	return status;
}

void Process::SetStatus(ProcessStatus outStatus)
{
	status = outStatus;
}

bool Process::operator== (int id)
{
	return (PID == id);
}

bool Process::NeedIO() const
{
	return false;
}

void Process::Print()
{
	std::cout << PID;
}


