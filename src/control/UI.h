#pragma once
///=//////////////////////////////////////////////////////=///
/// UI Class: reads and writes data to the standard output ///
///=//////////////////////////////////////////////////////=///

#include <iostream>
#include <windows.h>
#include "../data.h"
#include "Clock.h"

class UI
{
	/// Data Members
private:
	UIMode mode;
	const Clock* clk;

public:
	/// Output functions
	void WriteWarning(std::string msg);	// USEFULL for Debugging
	void WriteError(std::string msg);	// USEFULL for Debugging
	void PrintHeadline();
	void PrintUIModeMenu();
	void PrintTimeStamp();

	/// Constructor
	UI(Clock* aClk);

private:
	/// Color Control functions
	void ResetColor();
	void SetColor(Color color);

	/// Mode Management functions
	void SetMode(UIMode aMode);
};

