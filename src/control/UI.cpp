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
	std::cin.ignore(1000, '\n');
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
	std::cout << "_--------------------------------------------------------_" << std::endl;

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

/// Silent Mode Functions
void UI::PrintSilentModeStart()
{
	SetColor(PINK);
	std::cout << "Silent Mode .......\n";
	std::cout << "Simulation started...\n";
	ResetColor();
}

void UI::PrintSilentModeEnd()
{
	SetColor(PINK);
	std::cout << "Simulation ended...\n";
	ResetColor();
}

void UI::PrintOutputFileMsg(bool isCreated)
{
	if (isCreated)
	{
		SetColor(PINK);
		std::cout << "Output file created successfully...\n";
		ResetColor();
	}
	else
	{
		WriteError("Output file creation failed...\n");
	}
}

/// Input Related Functions
void UI::Wait()
{
	if (mode == INTERACTIVE)
	{
		std::cout << "Press any key to move to next step...";
		std::cin.get();
	}
	if (mode == STEP_BY_STEP)
	{
		Sleep(1000);
	}
}

std::string UI::GetInputFileName()
{
	SetColor(CYAN);
	std::cout << "Enter the name of the input file: ";
	ResetColor();
	std::string fileName;
	std::cin >> fileName;
	return fileName;
}

/// Constructor
UI::UI(Clock* aClk, Scheduler* aScheduler)
	:clk(aClk), scheduler(aScheduler), mode(INTERACTIVE)
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

/// Mode management
void UI::SetMode(UIMode aMode)
{
	mode = aMode;
}
