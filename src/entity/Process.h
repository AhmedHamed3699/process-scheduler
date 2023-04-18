#pragma once
///=//////////////////////////////////////////////////////////=///
///     Process Class: stores information about each process   ///
/// Created By scheduler maintained by scheduler and processor ///
///=//////////////////////////////////////////////////////////=///
#include "../data.h"
#include <iostream>

class Process
{
private:
	const int PID;
	Process* descendant;
	TimeInfo timeInfo;
	unsigned int IONumOfReq;
	unsigned int IOCounter;			//keep track of the current IO time and duration (as one process can have many IO)
	ProcessStatus status;			//any process created will have NEW as its initial status
public:
	Process(int id, unsigned int ioNum = 0);

	int GetID() const;
	Process* GetDescendant() const;
	void SetDescendant(Process* child);
	TimeInfo GetTimeInfo() const;
	void SetTimeInfo(TimeInfo tI);
	unsigned int GetIONumOfReq() const;			//can be used to know if the process would request IO or not
	void SetIONumOfReq(unsigned int ioNum);
	ProcessStatus GetStatus() const;
	void SetStatus(ProcessStatus outStatus);
	bool operator== (int id);

	//returns true if the process needs IO in this timestep
	//You may need to change its parameters depending on your implementation (ex: you may want to send the time to it)
	//You may also remove this method and just get the timeInfo of the process to check for IO time
	bool NeedIO() const;

	// for printing
	void Print();
};

