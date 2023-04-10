#include "Process.h"

Process::Process(int id, unsigned int ioNum): PID(id), IONumOfReq(ioNum), descendant(nullptr), IOCounter(0)
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

unsigned int Process::GetIONumOfReq() const
{
	return IONumOfReq;
}

void Process::SetIONumOfReq(unsigned int ioNum)
{
	IONumOfReq = ioNum;
}

bool Process::NeedIO() const
{
	return false;
}


