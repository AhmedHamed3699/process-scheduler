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
	/// TODO: This is just a test code. It will be removed later.
	ui.PrintHeadline();
	ui.PrintUIModeMenu();
	ui.PrintTimeStamp();

	scheduler.CreateProcessor(FCFS);
	scheduler.CreateProcessor(SJF);
	scheduler.CreateProcessor(RR);
	scheduler.CreateProcessor(FCFS);
	scheduler.CreateProcessor(SJF);

	scheduler.CreateNewProcess(0);
	scheduler.CreateNewProcess(2);
	scheduler.CreateNewProcess(3);
	scheduler.CreateNewProcess(4);
	scheduler.CreateNewProcess(5);
	scheduler.CreateNewProcess(6);
	scheduler.CreateNewProcess(7);
	scheduler.CreateNewProcess(8);
	scheduler.CreateNewProcess(9);
	scheduler.CreateNewProcess(10);
	scheduler.CreateNewProcess(11);

	clk.Step();

	ui.PrintTimeStamp();
	Simulation();
}

void Simulator::Simulation()
{

}