#include "Simulator.h"
#include <cstdlib>
#include <time.h>

bool Simulator::LoadInpuitFile()
{
	std::ifstream InFile;

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

		Queue<Pair<unsigned int, unsigned int>> IO;		//make a Queue to store IO_R and IO_D values in

		for (int i = 0; i < N; i++)
		{
			//read the values from the input file in the form (IO_R,IO_D)
			char lParenthesis, comma, rParenthesis;
			int IO_R, IO_D;
			InFile >> lParenthesis >> IO_R >> comma >> IO_D >> rParenthesis;

			//put IO_R and IO_D in a pair and push it in IO queue
			Pair<unsigned int, unsigned int> tempP(IO_R, IO_D);
			IO.enqueue(tempP);

			//to read the comma between each pair
			if (i < N - 1)
			{
				InFile >> comma;
			}
		}

		scheduler.CreateNewProcess(AT, PID, CT, N, IO);
	}


	///read the line SIGKILL Times (needs to get deleted if this line won't exist in the file)
	std::string uslessLine;

	getline(InFile, uslessLine);		//reads the enter key before SIGKILL Times line
	getline(InFile, uslessLine);		//reads SIGKILL Times line

	int PID, killTime;
	while (InFile >> killTime >> PID)	//loop till the end of the file
	{
		Pair<unsigned int, unsigned int> sigkillP(killTime, PID);
		scheduler.AddToSIGKILL(sigkillP);
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
	/// UI Mode part
	ui.PrintHeadline();
	ui.PrintSimulationParmas();
	ui.PrintUIModeMenu();
	if (ui.GetMode() == SILENT)
	{
		ui.PrintSilentModeStart();
	}

	Simulation();

	if (ui.GetMode() == SILENT)
	{
		ui.PrintSilentModeEnd();
		ui.PrintOutputFileMsg(false); /// TODO: change to true if create output file is implemented
	}
}

void Simulator::Simulation()
{
	/// TODO: Code in this block should be removed
	/// every functionality here should be re-factored into its appropriate class and/ or method
	/// this block is only for phase 1 testing

	srand(time(0));
	LoadInpuitFile();
	scheduler.CreateAllProcessors();

	while (true)
	{
		clk.Step();
		int kill = scheduler.SimulateKill();
		scheduler.ScheduleNext();
		scheduler.RunProcesses();
		scheduler.MoveFromRun();
		scheduler.MoveFromBLK();

		ui.PrintTimeStamp();

		if (kill != -1)
			ui.PrintProcessKilled(kill);
		if (scheduler.isDone())
			return;
		ui.Wait();
	}
}