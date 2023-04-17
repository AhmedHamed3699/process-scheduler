#pragma once
///=///////////////////////////////////////////////////=///
/// Scheduler: Main Class and controller of the program ///
///=///////////////////////////////////////////////////=///

#include "../data.h"
#include "ds/List.h"
#include "ds/Queue.h"
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
	///           Scheduler Lists           ///
	/// ////////////////////////////////// ///
private:
	List<Processor*> processors;
	Queue<Process*> NEWList;
	Queue<Process*> TRMList;
	Queue<Process*> BLKList;
	Process* IOProcess;

public:
	Scheduler()
		:simulationParameters(0, 0, 0, 0, 0, 0, 0, 0, 0)
	{

	}
};

