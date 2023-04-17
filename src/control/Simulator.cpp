#include "Simulator.h"

void Simulator::ShowMenu()
{

}

bool Simulator::LoadInpuitFile()
{
	ifstream InFile;
	InFile.open("test.txt");
	if (!InFile.is_open())
	{
		return false;	//maybe you would need to perform other actions when the file couldn't be opened
	}

	InFile.close();
	return true;
}

bool Simulator::CreateOutputFile()
{
	return true;
}

void Simulator::Run()
{
	Simulation();
}

void Simulator::Simulation()
{
	LoadInpuitFile();
}