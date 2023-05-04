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
	// prepares simulation by printing the headline, getting the input file name, and loading the input file
	bool PrepareSimulation();
};

