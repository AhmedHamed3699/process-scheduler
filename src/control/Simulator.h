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
	Schedular schedular;
	UI ui;

	void ShowMenu();
	bool LoadInpuitFile();
	bool CreateOutputFile();
	void Run();

	//void Run(mode : UIMode);
};

