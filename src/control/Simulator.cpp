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

void Simulator::Run(UIMode mode)
{
	/*
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

	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();


	scheduler.CreateNewProcess(20);
	scheduler.CreateNewProcess(21);
	scheduler.CreateNewProcess(22);
	scheduler.CreateNewProcess(23);

	scheduler.TerminateProcess(nullptr);
	scheduler.TerminateProcess(nullptr);
	scheduler.TerminateProcess(nullptr);
	scheduler.TerminateProcess(nullptr);

	scheduler.CreateNewProcess(24);
	scheduler.CreateNewProcess(25);
	scheduler.CreateNewProcess(26);
	scheduler.CreateNewProcess(27);

	scheduler.BlockProcess(nullptr);
	scheduler.BlockProcess(nullptr);
	scheduler.BlockProcess(nullptr);
	scheduler.BlockProcess(nullptr);

	scheduler.RunProcesses();

	clk.Step();

	ui.PrintTimeStamp();
	*/
	Simulation();
}

void Simulator::Simulation()
{
	LoadInpuitFile();
	while (true)
	{
		clk.Step();
		scheduler.CreateAllProcessors();
		scheduler.ScheduleNext(clk.GetTime());
		scheduler.RunProcesses();
		scheduler.MoveFromRun();
	}
}