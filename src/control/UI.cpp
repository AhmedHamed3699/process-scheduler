#include "UI.h"
#include <conio.h>
#include <iomanip>

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
	const unsigned int HEADLINE_WIDTH = 30;

	std::cout << std::setw((LINE_LENGTH - HEADLINE_WIDTH) / 2) << std::setfill(' ') << "";
	std::cout << ".-----------------------------." << std::endl;
	std::cout << std::setw((LINE_LENGTH - HEADLINE_WIDTH) / 2) << std::setfill(' ') << "";
	std::cout << "| Process Scheduler Simulator |" << std::endl;
	std::cout << std::setw((LINE_LENGTH - HEADLINE_WIDTH) / 2) << std::setfill(' ') << ""; // centers the headline
	std::cout << "'-----------------------------'" << std::endl;
	std::cout << std::endl;
	ResetColor();
}

void UI::PrintUIModeMenu()
{
	std::cout << "Select in what mode your want the simulation to run" << std::endl;
	std::cout << "\'I\' for Interactive, \'T\' for step by step, \'S\' for silent, \'D\' for debug: ";

	char aMode;
	std::cin >> aMode;
	std::cin.ignore(1000, '\n');

	switch (aMode)
	{
	case 'I':
	case 'i':
		SetMode(INTERACTIVE);
		break;
	case 'T':
	case 't':
		SetMode(STEP_BY_STEP);
		break;
	case 'S':
	case 's':
		SetMode(SILENT);
		break;
	case 'D':
	case 'd':
		SetMode(DEBUG);
		break;
	default:
		WriteWarning("Invalid input, please select one of the interface options");
		PrintUIModeMenu();
		break;
	}
}

void UI::PrintTimeStamp()
{
	// if the mode is silent, don't print anything
	if (mode == SILENT)
		return;

	SetColor(CYAN);
	std::cout << "_--------------------------------------------------------_" << std::endl;

	std::cout << "                   Current Timestamp: " << clk->GetTime() << std::endl;

	SetColor(BRIGHT_BLUE);
	std::cout << "-------------------  RDY PROCESSES  ----------------------" << std::endl;
	std::cout << scheduler->RDYListsToString();

	SetColor(GREY);
	std::cout << "-------------------  BLK PROCESSES  ----------------------" << std::endl;
	std::cout << scheduler->BLKListToString();

	SetColor(BRIGHT_GREEN);
	std::cout << "-------------------  RUN PROCESSES  ----------------------" << std::endl;
	std::cout << scheduler->RUNListToString();

	SetColor(PURPLE);
	std::cout << "-------------------  TRM PROCESSES  ----------------------" << std::endl;
	std::cout << scheduler->TRMListToString();

	SetColor(CYAN);
	std::cout << "-________________________________________________________-" << std::endl;
	ResetColor();
}

void UI::PrintSimulationParmas()
{
	SetColor(CYAN);
	std::cout << scheduler->SimulationParametersToString();
	ResetColor();
}

void UI::PrintProcessKilled(int PID)
{
	if (mode == SILENT) // if the mode is silent, don't print anything
		return;

	SetColor(DARK_YELLOW);
	std::cout << "Process " << PID << " Received SIGKILL" << " ...\n";
	ResetColor();
}

void UI::PrintWorkStealingAlert()
{
	SetColor(DARK_YELLOW);

	std::cout << "Work Stealing Is Running....\n";

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
		std::cout << "Press any key to move to next step...\n";
		_getch();
	}
	if (mode == STEP_BY_STEP)
	{
		Sleep(1000);
	}
}

std::string UI::GetInputFileName()
{
	SetColor(CYAN);
	std::cout << "Enter the name of the input file (\'d\' for default): ";
	ResetColor();
	std::string fileName;
	std::cin >> fileName;

	if (fileName == "d")
		fileName = "test.txt";

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

UIMode UI::GetMode()
{
	return mode;
}
