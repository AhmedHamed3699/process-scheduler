#pragma once
///=////////////////////////////////////////////=///
/// This file should contain structures and enums///
///=////////////////////////////////////////////=///
#include "ds/Queue.h"

/// CONSTANTS
#define LINE_LENGTH 106
#define NUM_PRECISION 3
#define WORK_STEALING true				// true if work stealing is enabled, false otherwise
#define OVER_HEATING true				// true if over heating is enabled, false otherwise
#define OVER_HEATING_PERCENT 2			// the percentage of which a processor will be over heated
#define OVER_HEATING_PERCENT_SCALE 1000  // the divider of the percent if 100 than the percent 0.02 
#define MAX_STEALING_LIMIT 0.4			// the maximum percentage of STEALING_LIMIT

/// ////////////////// ///
///     Enumerators    ///
/// ////////////////// ///

enum ProcessStatus {
	NEW,		//the process is in the NEW List (didn't arrive yet)
	RDY,		//the process is in a RDY List of a processor
	RUN,		//the process is being executed in a processor
	BLK,		//the process required an I/O
	TRM,		//the process has finished its execution (terminated)
	ORPH		//the process' parent is terminated so the process is now an orphan (must be killed immed)
};

enum ProcessorStatus {
	IDLE,
	BUSY,
	STOP
};

// Terminal Output colors codes
enum Color
{
	BLUE = 1,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	DARK_YELLOW,
	DEFAULT_WHITE,
	GREY,
	BRIGHT_BLUE,
	BRIGHT_GREEN,
	BRIGHT_CYAN,
	BRIGHT_RED,
	PINK,
	YELLOW,
	BRIGHT_WHITE,
	// not an actual color
	COLOR_SIZE
};

// Types of Processors
enum ProcessorType
{
	FCFS,
	SJF,
	RR,

	// not an actual size
	PROCESSOR_TYPE_SIZE
};

// Modes of UI
enum UIMode
{
	INTERACTIVE,
	STEP_BY_STEP,
	SILENT,
	DEBUG,
	// not an actual mode
	UI_MODE_SIZE
};


/// ////////////////// ///
///      Structs       ///
/// ////////////////// ///
struct TimeInfo
{
	unsigned int AT;	 //arrivalTime
	unsigned int RT;	 //responseTime
	unsigned int CT;	 //cpuTime
	unsigned int RCT;	 //remainingCpuTime
	unsigned int TT;	 //terminationTime
	unsigned int TRT;	 //turnaroundTime
	unsigned int WT;	 //waitingTime
	unsigned int currentIOD;	//IO duration for the current IO request
	unsigned int totalIOD;		//the total time spent by the process doing IO

	TimeInfo() :AT(0), RT(0), CT(0), RCT(0), TT(0), TRT(0), WT(0), currentIOD(0), totalIOD(0)
	{
	}
};

struct SimulationParameters
{
	unsigned int MAX_WAITING_TIME;
	unsigned int RR_TIME_SLICE;
	unsigned int N_FCFS;
	unsigned int N_SJF;
	unsigned int N_RR;
	unsigned int FORK_PROBABILITY;
	unsigned int STL;
	unsigned int RTF;
	unsigned int N_PROCESS;
	unsigned int OVERHEAT_TIME;

	SimulationParameters(
		unsigned int maxWaitingTime,
		unsigned int RRTimeSlice,
		unsigned int nFCFS,
		unsigned int nSJF,
		unsigned int nRR,
		unsigned int forkProbability,
		unsigned int stl,
		unsigned int rtf,
		unsigned int nProcess,
		unsigned int overheatTime
	)
		:MAX_WAITING_TIME(maxWaitingTime),
		RR_TIME_SLICE(RRTimeSlice),
		N_FCFS(nFCFS),
		N_SJF(nSJF),
		N_RR(nRR),
		FORK_PROBABILITY(forkProbability),
		STL(stl),
		RTF(rtf),
		N_PROCESS(nProcess),
		OVERHEAT_TIME(overheatTime)
	{}
};

template <typename firstItemType, typename secondItemType>
struct Pair
{
	firstItemType first;
	secondItemType second;

	Pair(firstItemType f, secondItemType s)
	{
		first = f;
		second = s;
	}

	void operator = (const Pair& original)
	{
		first = original.first;
		second = original.second;
	}
};