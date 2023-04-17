#include "UI.h"


/// Output Functions
void UI::WriteWarning(std::string msg)
{
	SetColor(YELLOW);
	std::cout << "Warning: " << msg << std::endl;
	ResetColor();
}

void UI::WriteError(std::string msg)
{
	SetColor(RED);
	std::cout << "ERROR: " << msg << std::endl;
	ResetColor();
}

void UI::PrintHeadline()
{
	SetColor(CYAN);
	std::cout << ".-----------------------------." << std::endl;
	std::cout << "| Process Scheduler Simulator |" << std::endl;
	std::cout << "'-----------------------------'" << std::endl;
	ResetColor();
}


/// Color Control Functions
void UI::ResetColor()
{
	HANDLE consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleOutputHandle, DEFAULT_WHITE);
}

void UI::SetColor(Color color)
{
	HANDLE consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleOutputHandle, color);
}

// Mode management
void UI::SetMode(UIMode aMode)
{
	mode = aMode;
}
