#pragma once
///=//////////////////////////////////////////////////////////=///
///     Process Class: stores information about each process   ///
/// Created By scheduler maintained by scheduler and processor ///
///=//////////////////////////////////////////////////////////=///
#include "../data.h"

class Process
{
private:
	const int PID;
	Process* descendant;
	TimeInfo timeInfo;
	ProcessStatus status;			//any process created will have NEW as its initial status
	bool isStolen;
	Queue<Pair<unsigned int, unsigned int>> IO;		//in Pair, first is IO_R and second is IO_D
public:
	Process(int id, unsigned int ioNum, Queue<Pair<unsigned int, unsigned int>>& outIO);

	int GetID() const;
	Process* GetDescendant() const;
	void SetDescendant(Process* child);

	/// ////////////////////////////////// ///
	///			  Time Information		   ///
	/// ////////////////////////////////// ///
	TimeInfo GetTimeInfo() const;
	void SetTimeInfo(TimeInfo tI);
	// Decrement the Remaining CPU Time of the process, used when executing the process
	void DecrementRCT();
	// Sets the Termination Time of the process, used when terminating the process
	void SetTT(unsigned int time);
	// Sets the response time of the process, used when adding a process to a processor
	void SetRT(unsigned int time);
	// Calculates adn Sets the turn around time of the process, used when terminating the process
	void CalcTRT();
	// Calculates and sets the total waiting time (WT) of the process, used when terminating the process
	void CalcWT();

	ProcessStatus GetStatus() const;
	void SetStatus(ProcessStatus outStatus);
	Pair<unsigned int, unsigned int> GetTopIOPair();	//it dequeues and return the first pair in the queue (if empty return Pair of (0,0)
	bool operator== (int id);
	bool operator< (Process* p);

	//returns true if the process needs IO in this timestep
	//You may need to change its parameters depending on your implementation (ex: you may want to send the time to it)
	//You may also remove this method and just get the timeInfo of the process to check for IO time
	bool NeedIO() const;

	bool IsStolen() const;
	void SetStolen(bool isStolen);

	// for UI and debugging
	std::string ToString();
};

