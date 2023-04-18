#pragma once
///=////////////////////////////////////////////////=///
/// Simulator Class Responsible of the file Handling ///
///=////////////////////////////////////////////////=///
#include <fstream>
#include <iostream>
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
	void Run();
	void Simulation();
};

