#pragma once
///=//////////////////////////////////////////////////////////=///
///     Process Class: stores information about each process   ///
/// Created By scheduler maintained by scheduler and processor ///
///=//////////////////////////////////////////////////////////=///
class Process
{
private:
	const int PID;
	Process* descendant;
	unsigned int IONumOfReq;
public:
	Process(int id, unsigned int ioNum = 0);

	int GetID() const;
	Process* GetDescendant() const;
	void SetDescendant(Process* Child);
	unsigned int GetIONumOfReq() const;			//can be used to know if the process would request IO or not
	void SetIONumOfReq(unsigned int ioNum);

	//returns true if the process needs IO in this timestep
	//You may need to change its parameters depending on your implementation (ex: you may want to send the time to it)
	bool NeedIO() const;						
};

