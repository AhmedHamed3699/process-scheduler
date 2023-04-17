#include "Simulator.h"

void Simulator::ShowMenu()
{

}

bool Simulator::LoadInpuitFile()
{
	return true;
}

bool Simulator::CreateOutputFile()
{
	return true;
}

void Simulator::Run()
{
	ui.PrintHeadline();
	ui.PrintUIModeMenu();
	ui.PrintTimeStamp();
	Simulation();
}

void Simulator::Simulation()
{

}