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
	std::cout << std::endl;
	ResetColor();
}

void UI::PrintUIModeMenu()
{
	std::cout << "Select in what mode your want the simulation to run" << std::endl;
	std::cout << "\'I\' for Interactive, \'T\' for step by step, \'S\' for silent: ";

	char aMode;
	std::cin >> aMode;


	// TODO: delete in phase 2
	WriteWarning("only Interactive mode is available in phase 1");


	switch (aMode)
	{
		// Enable in Phase 2, in phase 1 only mode is interactive
		#if 0
	case 'I':
		SetMode(INTERACTIVE);
		break;
	case 'T':
		SetMode(STEP_BY_STEP);
		break;
	case 'S':
		SetMode(SILENT)
			break;
		#endif
	default:
		SetMode(INTERACTIVE);
		break;
	}
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
