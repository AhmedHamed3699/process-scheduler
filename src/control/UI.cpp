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
	std::cout << "            .-----------------------------." << std::endl;
	std::cout << "            | Process Scheduler Simulator |" << std::endl;
	std::cout << "            '-----------------------------'" << std::endl;
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

void UI::PrintTimeStamp()
{
	SetColor(CYAN);
	std::cout << "-________________________________________________________-" << std::endl;

	std::cout << "                   Current Timestamp: " << clk->GetTime() << std::endl;

	SetColor(BRIGHT_BLUE);
	std::cout << "-------------------  RDY PROCESSES  ----------------------" << std::endl;
	scheduler->PrintRDYLists();

	SetColor(GREY);
	std::cout << "-------------------  BLK PROCESSES  ----------------------" << std::endl;
	scheduler->PrintBLKList();

	SetColor(BRIGHT_GREEN);
	std::cout << "-------------------  RUN PROCESSES  ----------------------" << std::endl;
	scheduler->PrintRUNList();

	SetColor(PURPLE);
	std::cout << "-------------------  TRM PROCESSES  ----------------------" << std::endl;
	scheduler->PrintTRMList();

	SetColor(CYAN);
	std::cout << "-________________________________________________________-" << std::endl;
	ResetColor();
}

// Constructor
UI::UI(Clock* aClk, Scheduler* aScheduler)
	:clk(aClk), scheduler(aScheduler)
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

// Mode management
void UI::SetMode(UIMode aMode)
{
	mode = aMode;
}
