#pragma once
///=////////////////////////////////////////////////=///
/// Simulator Class Responsible of the file Handling ///
///=////////////////////////////////////////////////=///

# include "Clock.h"
# include "Scheduler.h"
# include "UI.h"

class Simulator
{
public:

	Clock clk;
	Scheduler scheduler;
	UI ui{ &clk, &scheduler };
	
	Simulator() {};
	void ShowMenu();
	bool LoadInpuitFile();
	bool CreateOutputFile();
	void Run(UIMode mode = INTERACTIVE);
	void Simulation();
};

