#pragma once
///=///////////////////////////////////////////////////=///
/// Scheduler: Main Class and controller of the program ///
///=///////////////////////////////////////////////////=///

#include "Clock.h"
#include "../data.h"
#include "../ds/ArrayList.h"
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

	Clock* clk;
	SimulationParameters simulationParameters;

	/// ////////////////////////////////// ///
	///  Stats Data Members and counters   ///
	unsigned int maxWMigrations;
	unsigned int rtfMigrations;
	unsigned int killCount;

	/// ////////////////////////////////// ///
	///           Scheduler Lists          ///
	/// ////////////////////////////////// ///
	ArrayList<Processor*> processors;
	Queue<Process*> NEWList;
	Queue<Process*> TRMList;
	Queue<Process*> BLKList;
	Queue<Pair<unsigned int, unsigned int>> SIGKILL;	//In each Pair, first is the time and second is the PID
	Process* IOProcess;

	/// ////////////////////////////////// ///
	///    constructors and destructor     ///
	/// ////////////////////////////////// ///
public:
	Scheduler(Clock* clk);
	~Scheduler();
	int GetCurrentTime();

	/// ////////////////////////////////// ///
	///         Creation and setup         ///
	/// ////////////////////////////////// ///
	void CreateAllProcessors();
	// Create a new processor of the given type and add it to the list of processors
	void CreateProcessor(ProcessorType aType);
	// Create a new process with the given id and add it to the NEW list
	void CreateNewProcess(int id);
	// Create a new process with the all params and add it to the NEW list
	void CreateNewProcess(int AT, int PID, int CT,
		Queue<Pair<unsigned int, unsigned int>>& outIO);
	// Create a new forked process process
	Process* CreateForkedProcess(int PID, int AT, int CT);

	SimulationParameters GetSimulationParameters();
	void SetSimulationParameters(SimulationParameters sP);
	bool isDone(); // to know when to terminate the program

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
	// turns the simulation parameters into a string and returns it
	std::string SimulationParametersToString();

	/// ////////////////////////////////// ///
	///      Process State Management      ///
	/// ////////////////////////////////// ///
	// in phase 1 get the next process from the NEW list and add it to the 
	// first processor then the second and so on
	void ScheduleNext();
	void Schedule(Process* process, Processor* procesor);
	bool ScheduleNextFCFS(Process* process);
	bool ScheduleNextSJF(Process* process);
	bool ScheduleNextRR(Process* process);
	bool MigrateRR(Process* process);
	bool MigrateFCFS(Process* process);
	void ForkHandler(Process* process);
	// if process is not terminated then add it to the TRM list and change its state
	void TerminateProcess(Process* process);
	// if process is not blocked then add it to the BLK list and change its state
	void BlockProcess(Process* process);
	// it manages the block list and the processes in it
	void ManageBlock();
	// handles io_requests an move process to BLK list
	bool IO_RequestHandler(Process* process);
	//returns the Processor with the shortest time
	Processor* GetShortestRDYProcessor() const;
	//returns the Processor with the longest time
	Processor* GetLongestRDYProcessor() const;
	//returns the RR Processor with the shortest time 
	Processor* GetShortestRDYProcessorOfRR() const;
	//returns the SJF Processor with the shortest time 
	Processor* GetShortestRDYProcessorOfSJF() const;
	//returns the FCFS Processor with the shortest time 
	Processor* GetShortestRDYProcessorOfFCFS() const;
	// returns the processor with the shortest ready list
	Processor* GetShortestProcessorWithoutRUN() const;
	// returns the processor with the longest ready list
	Processor* GetLongestProcessorWithoutRUN() const;

	/// ////////////////////////////////// ///
	///        Simulation Functions        ///
	/// ////////////////////////////////// ///
	void RunProcesses();
	void MoveFromRun();
	void MoveFromBLK();

	// work stealing algorithm
	void WorkStealing();
	// calculates the stealing limit for two given processors
	double CalculateStealingLimit(Processor* largestProcessor, Processor* smallestProcessor);

	/// ////////////////////////////////// ///
	///    Statistics & output Functions   ///
	/// ////////////////////////////////// ///
	std::string TRMListStatsToString();
	void IncrementMaxWMigrations();
	void IncrementRTFMigrations();
	void IncrementKillCount();

	/// TIME STATS
	unsigned int CalculateAverageWaitTime();
	unsigned int CalculateTotalTurnaroundTime();
	unsigned int CalculateAverageTurnaroundTime();
	unsigned int CalculateAverageResponseTime();

	/// PROCESSOR STATS
	unsigned int* CalculateProcessorsUtilization();
	unsigned int* CalculateProcessorsLoad();
	unsigned int CalculateAverageProcessorsUtilization();

	/// OTHER FUNCTIONS STATS
	unsigned int CaculateWorkStealPercent();
	unsigned int GetNumberOfRTFMigrations();
	unsigned int GetNumberOfMaxWMigrations();
	unsigned int CalculateMaxWMigrationPercent();
	unsigned int CalculateRTFMigrationPercent();
	unsigned int CalculateKillCountPercent();
};

