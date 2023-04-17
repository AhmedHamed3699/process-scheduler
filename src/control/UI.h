#pragma once
///=//////////////////////////////////////////////////////=///
/// UI Class: reads and writes data to the standard output ///
///=//////////////////////////////////////////////////////=///

#include <iostream>
#include <windows.h>
#include "../data.h"

class UI
{
	/// Data Members
private:
	UIMode mode;

public:
	/// Output functions
	void WriteWarning(std::string msg);	// USEFULL for Debugging
	void WriteError(std::string msg);	// USEFULL for Debugging
	void PrintHeadline();
	void PrintUIModeMenu();

private:
	/// Color Control functions
	void ResetColor();
	void SetColor(Color color);

	/// Mode Management functions
	void SetMode(UIMode aMode);
};

