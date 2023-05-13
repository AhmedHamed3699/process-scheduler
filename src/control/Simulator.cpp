#include "Simulator.h"
#include <cstdlib>
#include <time.h>
#include <iomanip>

bool Simulator::LoadInpuitFile(std::string filePath)
{
	std::ifstream InFile;

	InFile.open(filePath);

	if (!InFile.is_open())
	{
		return false;	//maybe you would need to perform other actions when the file couldn't be opened
	}


	/// read the main data of the project & assign it to the simulator parameter in scheduler
	unsigned int maxWaitingTime, RRTimeSlice, nFCFS, nSJF,
		nRR, forkProbability, stl, rtf, nProcess, overheat_time;

	InFile >> nFCFS >> nSJF >> nRR;
	InFile >> RRTimeSlice;
	InFile >> rtf >> maxWaitingTime >> stl >> forkProbability >> overheat_time;
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
	sP.OVERHEAT_TIME = overheat_time;

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

		scheduler.CreateNewProcess(AT, PID, CT, IO);
	}


	///read the line SIGKILL Times (needs to get deleted if this line won't exist in the file)
	std::string uslessLine;

	getline(InFile, uslessLine);		//reads the enter key before SIGKILL Times line
	getline(InFile, uslessLine);		//reads SIGKILL Times line

	int PID, killTime;
	while (InFile >> killTime >> PID)	//loop till the end of the file
	{
		Pair<unsigned int, unsigned int> sigkillP(killTime, PID);
		ProcessorFCFS::AddToKill(sigkillP);
	}


	InFile.close();
	return true;
}

bool Simulator::CreateOutputFile()
{
	/// create the output file and validate it
	std::ofstream OutFile;
	OutFile.open("output.txt");
	if (!OutFile.is_open())
	{
		ui.PrintOutputFileMsg(false);
		return false;
	}

	/// Print TRM processes
	OutFile << "TT  PID AT  CT  IO_D WT  RT  TRT" << std::endl;
	OutFile << "================================" << std::endl;
	OutFile << scheduler.TRMListStatsToString();
	OutFile << "================================" << std::endl << std::endl;

	/// Print NUM of processes
	OutFile << "Processes: " << scheduler.GetSimulationParameters().N_PROCESS << std::endl;

	/// TIME AVERAGES
	OutFile << "Average Waiting Time     (WT): ";
	OutFile << std::setw(NUM_PRECISION) << std::setfill('0') << scheduler.CalculateAverageWaitTime() << std::endl;

	OutFile << "Average Response Time    (RT): ";
	OutFile << std::setw(NUM_PRECISION) << std::setfill('0') << scheduler.CalculateAverageResponseTime() << std::endl;

	OutFile << "Average Turnaround Time (TRT): ";
	OutFile << std::setw(NUM_PRECISION) << std::setfill('0') << scheduler.CalculateAverageTurnaroundTime() << std::endl;

	OutFile << std::endl;

	/// TODO: MIGRATION STATS

	/// WORK STEALING STATS
	OutFile << "Work Steal%: " << scheduler.CaculateWorkStealPercent() << "%" << std::endl;

	/// TODO: FORKING STATS

	/// TODO: KILLING STATS

	OutFile << std::endl;

	/// PROCESSOR STATS
	unsigned int numOfProcesors = scheduler.GetSimulationParameters().N_FCFS
		+ scheduler.GetSimulationParameters().N_SJF
		+ scheduler.GetSimulationParameters().N_RR;
	OutFile << "Processors: " << numOfProcesors;
	OutFile << " ["
		<< scheduler.GetSimulationParameters().N_FCFS << " FCFS, "
		<< scheduler.GetSimulationParameters().N_SJF << " SJF, "
		<< scheduler.GetSimulationParameters().N_RR << " RR]" << std::endl;

	/// CPU LOAD
	unsigned int* cpuLoad = scheduler.CalculateProcessorsLoad();
	OutFile << "Processors Load: \n";

	for (unsigned int i = 0; i < numOfProcesors; i++)
	{
		OutFile << "P" << i << ": " << cpuLoad[i] << "%,  ";
	}
	OutFile << std::endl << std::endl;

	delete[] cpuLoad;

	/// CPU UTILIZATION
	unsigned int* cpuUtilization = scheduler.CalculateProcessorsUtilization();
	OutFile << "Processors Utilization: \n";

	for (unsigned int i = 0; i < numOfProcesors; i++)
	{
		OutFile << "P" << i << ": " << cpuUtilization[i] << "%,  ";
	}
	OutFile << std::endl;

	delete[] cpuUtilization;

	OutFile << "Average Processor Utilization: " << scheduler.CalculateAverageProcessorsUtilization() << "%\n";

	OutFile << std::endl;


	/// OUTPUT MSG && close file
	OutFile.close();
	ui.PrintOutputFileMsg(true);
	return true;
}

void Simulator::Run()
{
	/// 1. prepare simulation by printing the headline, getting the input file name, and loading the input file
	if (!PrepareSimulation())
		return;

	/// 2. Run the simulation
	// Simulation Loop
	while (true)
	{
		// step the time
		clk.Step();

		// schedule the next process
		scheduler.ScheduleNext();

		// work stealing
		#if WORK_STEALING
		unsigned int STL = scheduler.GetSimulationParameters().STL;
		if (STL > 0 && clk.GetTime() % STL == 0)
		{
			scheduler.WorkStealing();
			ui.PrintWorkStealingAlert();
		}
		#endif

		// Over heating
		#if OVER_HEATING
		bool willOverHeat = rand() * OVER_HEATING_PERCENT_SCALE < OVER_HEATING_PERCENT;
		if (willOverHeat)
		{
			scheduler.OverHeating();
			//ui.PrintOverHeatingAlert();
		}
		#endif

		// manages process in BLK list
		scheduler.ManageBlock();
		// run the processes (calls the schedule algorithm for each processor and executes its current running task)
		scheduler.RunProcesses();

		// print the time stamp
		ui.PrintTimeStamp();

		// check if the simulation is done, and return
		if (scheduler.isDone())
			break;

		// wait for the user to press enter or wait for a specific time if the mode is STEP-BY-STEp
		ui.Wait();
	}

	/// 3. End Simulation
	// ending msg in silent mode
	if (ui.GetMode() == SILENT)
	{
		ui.PrintSilentModeEnd();
	}

	// creates the output file
	CreateOutputFile();
}

void Simulator::Simulation()
{
	/// TODO: Code in this block should be removed
	/// every functionality here should be re-factored into its appropriate class and/ or method
	/// this block is only for phase 1 testing
	/// TODO: CAN BE DELETED NOW, LEFT FOR REFERENCE

	while (true)
	{
		clk.Step();
		/// TODO: commented the most of the random moving code for testing purposes

		//int kill = scheduler.SimulateKill();
		scheduler.ScheduleNext();
		scheduler.RunProcesses();
		//scheduler.MoveFromRun();
		//scheduler.MoveFromBLK();

		ui.PrintTimeStamp();

		//if (kill != -1)
		//	ui.PrintProcessKilled(kill);
		if (scheduler.isDone())
			return;
		ui.Wait();
	}
}

bool Simulator::PrepareSimulation()
{
	/// 1. Print Headline
	ui.PrintHeadline();

	/// 2. Load Input File 
	std::string filePath = ui.GetInputFileName();
	if (!LoadInpuitFile(filePath))
	{
		ui.WriteError("File Not Found");
		return false;
	}

	/// 3. Get UI Mode
	ui.PrintSimulationParmas();
	ui.PrintUIModeMenu();
	if (ui.GetMode() == SILENT)
	{
		ui.PrintSilentModeStart();
	}

	/// 4. SET the random seed
	srand(time(0));

	/// 5. Create the processors
	scheduler.CreateAllProcessors();

	return true;
}
