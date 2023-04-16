#pragma once
///=////////////////////////////////////////////=///
/// This file should contain structures and enums///
///=////////////////////////////////////////////=///
#include "ds/Queue.h"

enum ProcessStatus {
	NEW,		//the process is in the NEW List (didn't arrive yet)
	RDY,		//the process is in a RDY List of a processor
	RUN,		//the process is being executed in a processor
	BLK,		//the process required an I/O
	TRM,		//the process has finished its execution (terminated)
	ORPH		//the process' parent is terminated so the process is now an orphan (must be killed immed)
};

struct TimeInfo
{
	unsigned int AT;	 //arrivalTime
	unsigned int RT;	 //responseTime
	unsigned int CT;	 //cpuTime
	unsigned int RCT;	 //remainingCpuTime
	unsigned int TT;	 //terminationTime
	unsigned int TRT;	 //turnaroundTime
	unsigned int WT;	 //waitingTime
	Queue<unsigned int> IO_R;	// IO RequestTime
	Queue<unsigned int> IO_D;	// IO Duration
};