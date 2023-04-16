#pragma once
///=////////////////////////////////////////////=///
///  Processor Class: runs and stores processes  ///
/// Created By scheduler maintained by scheduler ///
///=////////////////////////////////////////////=///
#include "../control/Scheduler.h"
#include "Process.h"

class Processor
{
protected:
	Scheduler* scheduler;
	Process* currentProcess;
	unsigned int totalBusyTime;
	unsigned int expectedFinishTime;
public:

};

