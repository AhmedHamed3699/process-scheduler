#pragma once
///=////////////////////////////////////////////////=///
/// Simulator Class Responsible of the file Handling ///
///=////////////////////////////////////////////////=///
#include <fstream>
#include <string>
#include "Clock.h"
#include "Scheduler.h"
#include "UI.h"

class Simulator
{
private:
	/// ////////////////////////////////// ///
	///       Private Data Members         ///
	/// ////////////////////////////////// ///
	// The Object containing the timestamp control
	Clock clk;
	// MAIN OBJECT: The Object containing the scheduler and the processors
	Scheduler scheduler{ &clk };
	// Contains User Interface Functions and Members
	UI ui{ &clk, &scheduler };

public:
	/// ////////////////////////////////// ///
	///       Constructor & Destructor    ///
	/// ////////////////////////////////// ///
	Simulator();
	~Simulator();

	/// ////////////////////////////////// ///
	///			I/O File Handling          ///
	/// ////////////////////////////////// ///
	bool LoadInpuitFile(std::string filePath);
	// creates the output file and returns true if the file is created successfully
	bool CreateOutputFile();

	/// ////////////////////////////////// ///
	///		START POINT OF SIMULATION      ///
	/// ////////////////////////////////// ///
	void Run();

	/// ////////////////////////////////// ///
	///         Private Functions          ///
	/// ////////////////////////////////// ///
private:
	// prepares simulation by printing the headline, gets the input file name, loads the input file
	// sets the UI mode, and creates processors, sets the random seed
	// returns false if the file is not found
	bool PrepareSimulation();
};

