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
	UI ui;

	void ShowMenu();
	bool LoadInpuitFile();
	bool CreateOutputFile();
	void Run();
	void Simulation();

	Simulator() {};

	//void Run(mode : UIMode);
};

