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
#include <iostream>
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
private:
	List<Processor*> processors;
	Queue<Process*> NEWList;
	Queue<Process*> TRMList;
	Queue<Process*> BLKList;
	Process* IOProcess;

	/// ////////////////////////////////// ///
	///    constructors and destructor     ///
	/// ////////////////////////////////// ///
public:
	Scheduler();


	/// ////////////////////////////////// ///
	///         Creation and setup         ///
	/// ////////////////////////////////// ///
	// Create a new processor of the given type and add it to the list of processors
	void CreateProcessor(ProcessorType aType);
	// Create a new process with the given id and add it to the NEW list
	void CreateNewProcess(int id);

	SimulationParameters GetSimulationParameters();
	void SetSimulationParameters(SimulationParameters sP);


	/// ////////////////////////////////// ///
	///           UI AID Functions         ///
	/// ////////////////////////////////// ///
	// Calls Print function for each processor
	void PrintRDYLists();
	// Calls Print for the TRM list
	void PrintTRMList();
	// Calls Print for the BLK list
	void PrintBLKList();
	// Calls Print for the NEW list
	void PrintRUNList();

	/// ////////////////////////////////// ///
	///      Process State Management      ///
	/// ////////////////////////////////// ///
	// in phase 1 get the next process from the NEW list and add it to the 
	// first processor then the second and so on
	void ScheduleNext();
	void ScheduleNextFCFS(Process* process);
	void ScheduleNextSJF(Process* process);
	void ScheduleNextRR(Process* process);
	// if process is not terminated then add it to the TRM list and change its state
	void TerminateProcess(Process* process);
	// if process is not blocked then add it to the BLK list and change its state
	void BlockProcess(Process* process);

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

