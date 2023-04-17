#include "UI.h"


/// Output Functions
void UI::WriteWarning(std::string msg)
{
}

void UI::WriteError(std::string msg)
{
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
