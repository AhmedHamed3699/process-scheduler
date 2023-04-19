#pragma once
///=//////////////////////////////////////////////////////=///
/// UI Class: reads and writes data to the standard output ///
///=//////////////////////////////////////////////////////=///

#include <iostream>
#include <windows.h>
#include "../data.h"
#include "Clock.h"
#include "Scheduler.h"

class UI
{
	/// ////////////////////////////////// ///
	///             Data Members           ///
	/// ////////////////////////////////// ///
private:
	UIMode mode;
	const Clock* clk;
	Scheduler* scheduler;

public:
	/// ////////////////////////////////// ///
	///			Output function	  	       ///
	/// ////////////////////////////////// ///
	void WriteWarning(std::string msg);	// USEFULL for Debugging
	void WriteError(std::string msg);	// USEFULL for Debugging
	// prints the headline (Project Name) of the program in the console 
	void PrintHeadline();
	// prompts the user for the simulation mode, and sets the mode
	void PrintUIModeMenu();
	// prints the current timestamp info into the console (RDY, TRM, BLK, RUN) lists and the time
	void PrintTimeStamp();
	// prints the simulation parameters into the console - For Debugging
	void PrintSimulationParmas();
	// print a msg indicaiting the a process is killed - For Debugging
	void PrintProcessKilled(int PID);

	/// ////////////////////////////////// ///
	///		  Silent Mode functions 	   ///
	/// ////////////////////////////////// ///
	// prints the start of the silent mode MSG
	void PrintSilentModeStart();
	// prints the end of the simulation mode MSG
	void PrintSilentModeEnd();
	// prints the output file is created successfully or not
	void PrintOutputFileMsg(bool isCreated);

	/// ////////////////////////////////// ///
	///       Input Related functions      ///
	///	////////////////////////////////// ///
	// if the Interactive mode is on waits for the user to press any key to continue
	// if STEP_BY_STEP waits 1 second
	void Wait();
	// prompts the user for the input file name and returns it
	std::string GetInputFileName();

	/// ////////////////////////////////// ///
	///            Constructor             ///
	/// ////////////////////////////////// ///
	UI(Clock* aClk, Scheduler* aScheduler);

private:
	/// ////////////////////////////////// ///
	///      Color Control functions       ///
	/// ////////////////////////////////// ///
	// resets the color of the console to the default color
	void ResetColor();
	// sets the color of the console to the given color
	void SetColor(Color color);

	/// ////////////////////////////////// ///
	///      Mode Management functions     ///
	/// ////////////////////////////////// ///
	// sets the mode of the UI
	void SetMode(UIMode aMode);
};

