#include "Simulator.h"
#include <cstdlib>
#include <time.h>

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


	/// read the main data of the project & assign it to the simulator parameter in scheduler
	unsigned int maxWaitingTime, RRTimeSlice, nFCFS, nSJF,
		nRR, forkProbability, stl, rtf, nProcess;

	InFile >> nFCFS >> nSJF >> nRR;
	InFile >> RRTimeSlice;
	InFile >> rtf >> maxWaitingTime >> stl >> forkProbability;
	InFile >> nProcess;

	SimulationParameters sP = scheduler.GetSimulationParameters();

	sP.MAX_WAITING_TIME = maxWaitingTime;
	sP.RR_TIME_SLICE = RRTimeSlice;
	sP.N_FCFS = nFCFS;
	sP.N_SJF = nSJF;
	sP.N_RR = nRR;
	sP.FORK_PROBABILITY = forkProbability;
	sP.STL = stl;
	sP.RTF = rtf;
	sP.N_PROCESS = nProcess;

	scheduler.SetSimulationParameters(sP);


	/// read Infos for each process
	for (unsigned int i = 0; i < nProcess; i++)
	{
		int AT, PID, CT, N;
		InFile >> AT >> PID >> CT >> N;

		scheduler.CreateNewProcess(AT,PID,CT,N);


		for (int i = 0; i < N; i++)
		{
			//read the values from the input file in the form (IO_R,IO_D)
			char lParenthesis, comma, rParenthesis;
			int IO_R, IO_D;
			InFile >> lParenthesis >> IO_R >> comma >> IO_D >> rParenthesis;

			// TODO: add the IO_R and IO_D values to the process

			//to read the comma between each pair
			if (i < N - 1)
			{
				InFile >> comma;
			}
		}
	}


	///read the line SIGKILL Times (needs to get deleted if this line won't exist in the file)
	string uslessLine;

	getline(InFile, uslessLine);		//reads the enter key before SIGKILL Times line
	getline(InFile, uslessLine);		//reads SIGKILL Times line

	int PID, killTime;
	while (InFile >> killTime >> PID)	//loop till the end of the file
	{
		// TODO: add the killTime and PID to SIGKILL List 
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
	srand(time(0));
	LoadInpuitFile();
	scheduler.CreateAllProcessors();

	ui.PrintHeadline();
	ui.PrintUIModeMenu();

	while (true)
	{
		clk.Step();
		scheduler.ScheduleNext(clk.GetTime());
		scheduler.RunProcesses(clk.GetTime());
		scheduler.MoveFromRun(clk.GetTime());
		scheduler.MoveFromBLK(clk.GetTime());
		scheduler.SimulateKill();
		ui.PrintTimeStamp();
		if (scheduler.isDone())
			return;
		ui.Wait();
	}
}