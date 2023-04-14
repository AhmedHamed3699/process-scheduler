#pragma once
///=////////////////////////////////////////////=///
/// This file should contain structures and enums///
///=////////////////////////////////////////////=///

struct TimeInfo
{
	unsigned int AT;	 //arrivalTime
	unsigned int RT;	 //responseTime
	unsigned int CT;	 //cpuTime
	unsigned int RCT;	 //remainingCpuTime
	unsigned int TT;	 //terminationTime
	unsigned int TRT;	 //turnaroundTime
	unsigned int WT;	 //waitingTime
	unsigned int[] IO_R; //IO_RequestTime
	unsigned int[] IO_D; //IO_Duration
};