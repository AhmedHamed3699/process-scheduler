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
	bool LoadInpuitFile();
	bool CreateOutputFile();
	void Run();
	void Simulation();
};

