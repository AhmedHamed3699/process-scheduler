#pragma once
///=///////////////////////////////////////////////////=///
/// Scheduler: Main Class and controller of the program ///
///=///////////////////////////////////////////////////=///

#include "../data.h"
#include "../ds/List.h"
#include "../ds/Queue.h"
#include "../entity/Process.h"
#include "../entity/Processor.h"
#include "../entity/ProcessorFCFS.h"
#include "../entity/ProcessorSJF.h"
#include "../entity/ProcessorRR.h"
#include <string>

class Scheduler
{

	/// ////////////////////////////////// ///
	///  Scheduler Data Members and flags  ///
	/// ////////////////////////////////// ///
private:
	SimulationParameters simulationParameters;
	int nextProcessorIndex = 0; /// TODO: remove this later (Phase 2)

	/// ////////////////////////////////// ///
	///           Scheduler Lists          ///
	/// ////////////////////////////////// ///
	List<Processor*> processors;
	Queue<Process*> NEWList;
	Queue<Process*> TRMList;
	Queue<Process*> BLKList;
	Queue<Pair<unsigned int, unsigned int>> SIGKILL;	//In each Pair, first is the time and second is the PID
	Process* IOProcess;

	/// ////////////////////////////////// ///
	///    constructors and destructor     ///
	/// ////////////////////////////////// ///
public:
	Scheduler();


	/// ////////////////////////////////// ///
	///         Creation and setup         ///
	/// ////////////////////////////////// ///
	void CreateAllProcessors();
	// Create a new processor of the given type and add it to the list of processors
	void CreateProcessor(ProcessorType aType);
	// Create a new process with the given id and add it to the NEW list
	void CreateNewProcess(int id);
	// Create a new process with the all params and add it to the NEW list
	void CreateNewProcess(int AT, int PID, int CT, int N,
		Queue<Pair<unsigned int, unsigned int>>& outIO);

	SimulationParameters GetSimulationParameters();
	void SetSimulationParameters(SimulationParameters sP);
	bool isDone(); // to know when to terminate the program
	void AddToSIGKILL(Pair<unsigned int, unsigned int> outP);

	/// ////////////////////////////////// ///
	///           UI AID Functions         ///
	/// ////////////////////////////////// ///
	// Calls toString function for each processor and returns the result as a string
	std::string RDYListsToString();
	// Calls toString for the TRM list and returns the result as a string
	std::string TRMListToString();
	// Calls toString for the BLK list and returns the result as a string
	std::string BLKListToString();
	// Calls toString for the RUN list and returns the result as a string
	std::string RUNListToString();

	/// ////////////////////////////////// ///
	///      Process State Management      ///
	/// ////////////////////////////////// ///
	// in phase 1 get the next process from the NEW list and add it to the 
	// first processor then the second and so on
	void ScheduleNext(int currentTime);
	void ScheduleNextFCFS(Process* process);
	void ScheduleNextSJF(Process* process);
	void ScheduleNextRR(Process* process);
	// if process is not terminated then add it to the TRM list and change its state
	void TerminateProcess(Process* process);
	// if process is not blocked then add it to the BLK list and change its state
	void BlockProcess(Process* process);

	/// ////////////////////////////////// ///
	///        Simulation Functions        ///
	/// ////////////////////////////////// ///
	void RunProcesses(int CurrentTime);
	void MoveToRDY(Process* process);
	void MoveFromRun(int CurrentTime);
	void MoveFromBLK(int CurrentTime);
	void SimulateKill();

	/// ////////////////////////////////// ///
	///        Statistics Functions        ///
	/// ////////////////////////////////// ///
	unsigned int CalculateAverageWaitTime();
	unsigned int CalculateAverageTurnaroundTime();
	unsigned int CalculateAverageResponseTime();
	unsigned int* CalculateProcessorsUtilization();
	unsigned int* CalculateProcessorsLoad();
	unsigned int CalculateAverageProcessorsUtilization();
};

