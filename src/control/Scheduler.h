#pragma once
///=///////////////////////////////////////////////////=///
/// Scheduler: Main Class and controller of the program ///
///=///////////////////////////////////////////////////=///

#include "../data.h"
#include "../ds/List.h"
#include "../ds/Queue.h"
#include "../entity/Process.h"
#include "../entity/Processor.h"


class Scheduler
{

	/// ////////////////////////////////// ///
	///  Scheduler Data Members and flags  ///
	/// ////////////////////////////////// ///
private:
	SimulationParameters simulationParameters;

	/// ////////////////////////////////// ///
	///           Scheduler Lists          ///
	/// ////////////////////////////////// ///
private:
	List<Processor*> processors;
	Queue<Process*> NEWList;
	Queue<Process*> TRMList;
	Queue<Process*> BLKList;
	Process* IOProcess;

public:
	Scheduler()
		:simulationParameters(1, 22, 33, 44, 55, 66, 77, 88, 424)
	{
		// TODO: reomve later
		cout << "fork prob " << simulationParameters.FORK_PROBABILITY << endl;
		cout << "mwt " << simulationParameters.MAX_WAITING_TIME << endl;
		cout << "n fcfs " << simulationParameters.N_FCFS << endl;
		cout << "n rr " << simulationParameters.N_RR << endl;
		cout << "n sjf " << simulationParameters.N_SJF << endl;
		cout << "n process " << simulationParameters.N_PROCESS << endl;
		cout << "rtf " << simulationParameters.RTF << endl;
		cout << "stl " << simulationParameters.STL << endl;
	}
};

