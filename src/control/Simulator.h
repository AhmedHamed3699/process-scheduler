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

	Clock clk;
	Scheduler scheduler{ &clk };
	UI ui{ &clk, &scheduler };

public:

	Simulator() {};
	bool LoadInpuitFile(std::string filePath);
	bool CreateOutputFile();
	void Run();
	void Simulation();

	/// ////////////////////////////////// ///
	///         Private Functions          ///
	/// ////////////////////////////////// ///
private:
	// prepares simulation by printing the headline, gets the input file name, loads the input file
	// sets the UI mode, and creates processors, sets the random seed
	// returns false if the file is not found
	bool PrepareSimulation();
};

