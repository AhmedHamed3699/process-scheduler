#include "Scheduler.h"
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>

/// ////////////////////////////////// ///
///    constructors and destructor     ///
/// ////////////////////////////////// ///
Scheduler::Scheduler(Clock* clk)
	:simulationParameters(0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
	IOProcess(nullptr)
{
	this->clk = clk;
}

Scheduler::~Scheduler()
{
	for (int i = 1; i <= processors.GetLength(); i++)
	{
		delete processors.GetEntry(i);
		processors.Remove(i);
	}

	for (int i = 0; i < TRMList.getSize(); i++)
	{
		delete TRMList.peekFront();
		TRMList.dequeue();
	}
}

int Scheduler::GetCurrentTime()
{
	return clk->GetTime();
}

/// ////////////////////////////////// ///
///         Creation and setup         ///
/// ////////////////////////////////// ///
void Scheduler::CreateAllProcessors()
{
	for (int i = 0; i < simulationParameters.N_FCFS; i++)
		CreateProcessor(FCFS);

	for (int i = 0; i < simulationParameters.N_SJF; i++)
		CreateProcessor(SJF);

	for (int i = 0; i < simulationParameters.N_RR; i++)
		CreateProcessor(RR);
}

void Scheduler::CreateProcessor(ProcessorType aType)
{
	Processor* newProcessor;
	switch (aType)
	{
	case FCFS:
		newProcessor = new ProcessorFCFS(this);
		break;
	case SJF:
		newProcessor = new ProcessorSJF(this);
		break;
	case RR:
		newProcessor = new ProcessorRR(this);
		break;
	default:
		newProcessor = new ProcessorFCFS(this);
		break;
	}

	processors.Insert(processors.GetLength() + 1, newProcessor);
}

void Scheduler::CreateNewProcess(int id)
{
	Queue<Pair<unsigned int, unsigned int>> emptyQ;		//empty Queue to initialize process with
	Process* newProcess = new Process(id, emptyQ);
	newProcess->SetStatus(NEW);
	// add processor to the NEW list
	NEWList.enqueue(newProcess);
}

void Scheduler::CreateNewProcess(int AT, int PID, int CT,
	Queue<Pair<unsigned int, unsigned int>>& outIO)
{
	// create new process
	Process* newProcess = new Process(PID, outIO);
	newProcess->SetStatus(NEW);

	TimeInfo timeInfo;
	timeInfo.AT = AT;
	timeInfo.CT = CT;
	timeInfo.RCT = CT;

	newProcess->SetTimeInfo(timeInfo);

	// add processor to the NEW list
	NEWList.enqueue(newProcess);
}

Process* Scheduler::CreateForkedProcess(int PID, int AT, int CT)
{
	Queue<Pair<unsigned int, unsigned int>> emptyQ;	 //empty Queue to initialize process with
	Process* newProcess = new Process(PID, emptyQ);
	newProcess->SetStatus(NEW);

	TimeInfo timeInfo;
	timeInfo.AT = AT;
	timeInfo.CT = CT;
	timeInfo.RCT = CT;

	newProcess->SetTimeInfo(timeInfo);

	return newProcess;
}

SimulationParameters Scheduler::GetSimulationParameters()
{
	return simulationParameters;
}

void Scheduler::SetSimulationParameters(SimulationParameters sP)
{
	simulationParameters = sP;
}

bool Scheduler::isDone()
{
	return (simulationParameters.N_PROCESS == TRMList.getSize());
}

/// ////////////////////////////////// ///
///           UI AID Functions         ///
/// ////////////////////////////////// ///
std::string  Scheduler::RDYListsToString()
{
	std::string str = "";
	for (int i = 1; i <= processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i);
		str += "Processor " + std::to_string(i) + " ";
		str += processor->ToString();
	}
	return str;
}

std::string Scheduler::TRMListToString()
{
	std::string str = "";
	str += std::to_string(TRMList.getSize()) + " TRM: ";
	str += TRMList.ToString();
	str += "\n";
	return str;
}

std::string Scheduler::BLKListToString()
{
	std::string str = "";
	str += std::to_string(BLKList.getSize()) + " BLK: ";
	str += BLKList.ToString();
	str += "\n";
	return str;
}

std::string Scheduler::RUNListToString()
{
	std::string* RUNList = new std::string[processors.GetLength()];
	unsigned int runListSize = 0;

	for (int i = 1; i <= processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i);
		if (processor->GetCurrentProcess() != nullptr)
		{
			RUNList[runListSize++] = std::to_string(processor->GetCurrentProcess()->GetID()) + "(P" + std::to_string(i) + ")";
		}
	}

	std::string str = "";

	str += std::to_string(runListSize) + " RUN: ";
	for (unsigned int i = 0; i < runListSize; i++)
	{
		str += RUNList[i];
		if (i < runListSize - 1)
		{
			str += ", ";
		}
	}

	if (runListSize == 0)
	{
		str += "Empty List";
	}

	str += "\n";
	return str;
}

std::string Scheduler::SimulationParametersToString()
{
	std::stringstream ss;
	ss << "Simulation Parameters:\n";
	ss << ".";
	ss << std::setfill('-') << std::setw(LINE_LENGTH - 2) << ".\n";
	ss << "| NP " << std::setfill('0') << std::setw(NUM_PRECISION) << simulationParameters.N_PROCESS;
	ss << " | N_FCFS " << std::setfill('0') << std::setw(NUM_PRECISION) << simulationParameters.N_FCFS;
	ss << " | N_RR " << std::setfill('0') << std::setw(NUM_PRECISION) << simulationParameters.N_RR;
	ss << " | N_SJF " << std::setfill('0') << std::setw(NUM_PRECISION) << simulationParameters.N_SJF;
	ss << " | FB " << std::setfill('0') << std::setw(NUM_PRECISION) << simulationParameters.FORK_PROBABILITY;
	ss << " | MWT " << std::setfill('0') << std::setw(NUM_PRECISION) << simulationParameters.MAX_WAITING_TIME;
	ss << " | TS " << std::setfill('0') << std::setw(NUM_PRECISION) << simulationParameters.RR_TIME_SLICE;
	ss << " | RTF " << std::setfill('0') << std::setw(NUM_PRECISION) << simulationParameters.RTF;
	ss << " | STL " << std::setfill('0') << std::setw(NUM_PRECISION) << simulationParameters.STL;
	ss << " | OHT " << std::setfill('0') << std::setw(NUM_PRECISION) << simulationParameters.OVERHEAT_TIME;
	ss << " |\n";
	ss << "'" << std::setfill('-') << std::setw(LINE_LENGTH - 2) << "'\n";
	return ss.str();
}

/// ////////////////////////////////// ///
///     Process State Management       ///
/// ////////////////////////////////// ///
void Scheduler::ScheduleNext()
{
	while (!NEWList.isEmpty())
	{
		Process* process = NEWList.peekFront();

		TimeInfo timeInfo = process->GetTimeInfo();
		if (timeInfo.AT != clk->GetTime())
			return;

		NEWList.dequeue();

		Processor* processor = GetShortestRDYProcessor();

		if (processor == nullptr)
		{
			return;
		}

		// schedule the process
		processor->AddProcessToList(process);
	}
}

void Scheduler::Schedule(Process* process, Processor* processor)
{
	processor->AddProcessToList(process);
}

bool Scheduler::ScheduleNextFCFS(Process* process)
{
	Processor* processorFCFS = GetShortestRDYProcessorOfFCFS();

	//false means that no FCFS processors in the system
	if (processorFCFS == nullptr)
		return false;

	processorFCFS->AddProcessToList(process);
	return true;
}

bool Scheduler::ScheduleNextSJF(Process* process)
{
	Processor* processorSJF = GetShortestRDYProcessorOfSJF();

	//false means that no SJF processors in the system
	if (processorSJF == nullptr)
		return false;

	processorSJF->AddProcessToList(process);
	return true;
}

bool Scheduler::ScheduleNextRR(Process* process)
{
	Processor* processorRR = GetShortestRDYProcessorOfRR();

	//false means that no RR processors in the system
	if (processorRR == nullptr)
		return false;

	processorRR->AddProcessToList(process);
	return true;
}

bool Scheduler::MigrateRR(Process* process)
{
	if (process->GetTimeInfo().RCT < simulationParameters.RTF)
	{
		//migrate the process to a SJF processor
		bool isSuccessful = ScheduleNextSJF(process);

		//if the migration failed due to not having any SJF processors
		if (!isSuccessful)
			return false;

		return true;
	}

	return false;
}

void Scheduler::ForkHandler(Process* process)
{
	// checks if there is no FCFS processors or no running process
	if (simulationParameters.N_FCFS == 0 || process == nullptr)
		return;

	int Rand = rand() % 101;
	if (Rand <= simulationParameters.FORK_PROBABILITY)
	{
		int id = simulationParameters.N_PROCESS + 10;
		Process* ForkedProcess = CreateForkedProcess(id, clk->GetTime(), process->GetTimeInfo().RCT);
		ForkedProcess->SetForked(true);		// set the forked flag to true
		ScheduleNextFCFS(ForkedProcess);
		process->SetDescendant(ForkedProcess);
		simulationParameters.N_PROCESS++;
	}
}

void Scheduler::TerminateProcess(Process* process)
{
	if (process->GetStatus() == TRM)
	{
		return;
	}
	process->SetCurrentProcessor(nullptr);
	process->SetStatus(TRM);
	process->SetTT(clk->GetTime());
	process->CalcTRT();
	process->CalcWT();
	TRMList.enqueue(process);
}

void Scheduler::BlockProcess(Process* process)
{
	if (process->GetStatus() == BLK)
	{
		return;
	}
	process->SetCurrentProcessor(nullptr);
	process->SetStatus(BLK);
	BLKList.enqueue(process);
}

void Scheduler::ManageBlock()
{
	if (BLKList.isEmpty())
		return;

	//get the first process in the block list
	Process* blockedProcess = BLKList.peekFront();

	//decrement the currentIOD by one 
	TimeInfo timeInfo = blockedProcess->GetTimeInfo();
	timeInfo.currentIOD--;
	blockedProcess->SetTimeInfo(timeInfo);

	//check if the process finished its IO duration
	if (timeInfo.currentIOD <= 0)
	{
		//remove the process from the Block List and move it to the shortest RDY Queue
		BLKList.dequeue();
		Processor* shortestProcessor = GetShortestRDYProcessor();
		shortestProcessor->AddProcessToList(blockedProcess);
	}

	//Note: when handling the IO Request we should first call the ManageBlock function then move the processes from the processors to the BLKList
}

bool Scheduler::IO_RequestHandler(Process* process)
{
	TimeInfo timeinfo = process->GetTimeInfo();
	if (process->NeedIO(clk->GetTime())) // checks if process needs IO this timestamp
	{
		timeinfo.currentIOD = process->GetTopIOPair().second;
		timeinfo.totalIOD += timeinfo.currentIOD;
		process->SetTimeInfo(timeinfo);
		BlockProcess(process);
		return true;
	}
	return false;
}

Processor* Scheduler::GetShortestRDYProcessor() const
{
	if (processors.IsEmpty())
	{
		return nullptr;
	}


	int shortestProcessorIndex = 1;
	Processor* shortestProcessor = processors.GetEntry(shortestProcessorIndex);
	while (shortestProcessor && shortestProcessor->GetStatus() == STOP)
	{
		shortestProcessor = processors.GetEntry(++shortestProcessorIndex);
	}

	if (shortestProcessor == nullptr)
	{
		return nullptr;
	}

	for (int i = 2; i <= processors.GetLength(); i++)
	{
		Processor* tempProcessor = processors.GetEntry(i);

		/// ADDED for overheating by Amir
		if (tempProcessor->GetStatus() == STOP)
			continue;

		if (shortestProcessor->GetExpectedFinishTime() > tempProcessor->GetExpectedFinishTime())
		{
			shortestProcessor = tempProcessor;
		}
	}

	return shortestProcessor;
}

Processor* Scheduler::GetLongestRDYProcessor() const
{
	if (processors.IsEmpty())
	{
		return nullptr;
	}

	int longestProcessorIndex = 1;
	Processor* longestProcessor = processors.GetEntry(longestProcessorIndex);
	while (longestProcessor && longestProcessor->GetStatus() == STOP)
	{
		longestProcessor = processors.GetEntry(++longestProcessorIndex);
	}

	if (longestProcessor == nullptr)
	{
		return nullptr;
	}

	for (int i = 2; i <= processors.GetLength(); i++)
	{
		Processor* tempProcessor = processors.GetEntry(i);

		/// ADDED for overheating by Amir
		if (tempProcessor->GetStatus() == STOP)
			continue;

		if (longestProcessor->GetExpectedFinishTime() < tempProcessor->GetExpectedFinishTime())
		{
			longestProcessor = tempProcessor;
		}
	}
	return longestProcessor;
}

Processor* Scheduler::GetShortestRDYProcessorOfRR() const
{
	int counter = simulationParameters.N_FCFS + simulationParameters.N_SJF + 1;

	//check if there are any RR Processors
	if (counter > processors.GetLength())
		return nullptr;

	Processor* shortestRRProcessor = processors.GetEntry(counter);

	/// ADDED for overheating by Amir
	while (shortestRRProcessor && shortestRRProcessor->GetStatus() == STOP)
	{
		shortestRRProcessor = processors.GetEntry(++counter);
	}

	if (shortestRRProcessor == nullptr)
	{
		return nullptr;
	}

	for (int i = counter + 1; i <= processors.GetLength(); i++)
	{
		Processor* tempProcessor = processors.GetEntry(i);

		/// ADDED for overheating by Amir
		if (tempProcessor->GetStatus() == STOP)
			continue;

		if (shortestRRProcessor->GetExpectedFinishTime() > tempProcessor->GetExpectedFinishTime())
		{
			shortestRRProcessor = tempProcessor;
		}
	}

	return shortestRRProcessor;
}

Processor* Scheduler::GetShortestRDYProcessorOfSJF() const
{
	//check if there are any SJF Processors
	if (simulationParameters.N_SJF <= 0)
		return nullptr;

	int counter, size;

	counter = simulationParameters.N_FCFS + 1;
	size = counter + simulationParameters.N_SJF;

	Processor* shortestSJFProcessor = processors.GetEntry(counter);
	/// ADDED for overheating by Amir
	while (shortestSJFProcessor && shortestSJFProcessor->GetStatus() == STOP)
	{
		shortestSJFProcessor = processors.GetEntry(++counter);
	}

	if (shortestSJFProcessor == nullptr)
	{
		return nullptr;
	}

	for (int i = counter + 1; i < size; i++)
	{
		Processor* tempProcessor = processors.GetEntry(i);

		/// ADDED for overheating by Amir
		if (tempProcessor->GetStatus() == STOP)
			continue;

		if (shortestSJFProcessor->GetExpectedFinishTime() > tempProcessor->GetExpectedFinishTime())
		{
			shortestSJFProcessor = tempProcessor;
		}
	}

	return shortestSJFProcessor;
}

Processor* Scheduler::GetShortestRDYProcessorOfFCFS() const
{
	//check if there are any FCFS Processors
	if (simulationParameters.N_FCFS <= 0)
		return nullptr;

	int counter, size;

	counter = 1;
	size = counter + simulationParameters.N_FCFS;

	Processor* shortestFCFSProcessor = processors.GetEntry(counter);
	/// ADDED for overheating by Amir
	while (shortestFCFSProcessor && shortestFCFSProcessor->GetStatus() == STOP)
	{
		shortestFCFSProcessor = processors.GetEntry(++counter);
	}

	if (shortestFCFSProcessor == nullptr)
	{
		return nullptr;
	}

	for (int i = counter + 1; i < size; i++)
	{
		Processor* tempProcessor = processors.GetEntry(i);

		/// ADDED for overheating by Amir
		if (tempProcessor->GetStatus() == STOP)
			continue;

		if (shortestFCFSProcessor->GetExpectedFinishTime() > tempProcessor->GetExpectedFinishTime())
		{
			shortestFCFSProcessor = tempProcessor;
		}
	}

	return shortestFCFSProcessor;
}

Processor* Scheduler::GetShortestProcessorWithoutRUN() const
{
	if (processors.IsEmpty())
	{
		return nullptr;
	}

	int shortestProcessorIndex = 1;
	Processor* shortestProcessor = processors.GetEntry(shortestProcessorIndex);
	/// ADDED for overheating by Amir
	while (shortestProcessor && shortestProcessor->GetStatus() == STOP)
	{
		shortestProcessor = processors.GetEntry(++shortestProcessorIndex);
	}

	if (shortestProcessor == nullptr)
	{
		return nullptr;
	}

	for (int i = 2; i <= processors.GetLength(); i++)
	{
		Processor* tempProcessor = processors.GetEntry(i);

		/// ADDED for overheating by Amir
		if (shortestProcessor->GetStatus() == STOP)
			continue;

		if (shortestProcessor->GetTotalReadyTime() > tempProcessor->GetTotalReadyTime())
		{
			shortestProcessor = tempProcessor;
		}
	}

	return shortestProcessor;
}

Processor* Scheduler::GetLongestProcessorWithoutRUN() const
{
	if (processors.IsEmpty())
	{
		return nullptr;
	}

	int longestProcessorIndex = 1;
	Processor* longestProcessor = processors.GetEntry(longestProcessorIndex);
	/// Added for overheating by Amir
	while (longestProcessor && longestProcessor->GetStatus() == STOP)
	{
		longestProcessor = processors.GetEntry(++longestProcessorIndex);
	}

	if (longestProcessor == nullptr)
	{
		return nullptr;
	}

	for (int i = 2; i <= processors.GetLength(); i++)
	{
		Processor* tempProcessor = processors.GetEntry(i);

		/// ADDED for over heating by Amir
		if (tempProcessor->GetStatus() == STOP)
			continue;

		if (longestProcessor->GetTotalReadyTime() < tempProcessor->GetTotalReadyTime())
		{
			longestProcessor = tempProcessor;
		}
	}
	return longestProcessor;
}

/// ////////////////////////////////// ///
///        Simulation Functions        ///
/// ////////////////////////////////// ///

void Scheduler::RunProcesses()
{
	for (int i = 0; i < processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i + 1);
		processor->ExecuteProcess(clk->GetTime());
	}
}


void Scheduler::MoveFromRun()
{
	for (int i = 0; i < processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i + 1);
		Process* CurrentProcess = processor->GetCurrentProcess();
		if (CurrentProcess == nullptr)
			continue;

		TimeInfo timeInfo = CurrentProcess->GetTimeInfo();

		if (timeInfo.RT + timeInfo.AT == clk->GetTime())
			continue;

		int probability = (rand() % 100) + 1;
		if (probability <= 15)
		{
			processor->SetStatus(IDLE);
			processor->SetCurrentProcess(nullptr);
			BlockProcess(CurrentProcess);
		}
		else if (probability >= 20 && probability <= 30)
		{
			processor->SetStatus(IDLE);
			processor->SetCurrentProcess(nullptr);
			Schedule(CurrentProcess, processor);
		}
		else if (probability >= 50 && probability <= 60)
		{
			processor->SetStatus(IDLE);
			processor->SetCurrentProcess(nullptr);
			TerminateProcess(CurrentProcess);
		}
	}
}

void Scheduler::MoveFromBLK()
{
	int probability = (rand() % 100) + 1;
	if (BLKList.isEmpty())
		return;

	Process* BlockedProcess = BLKList.peekFront();

	if (probability < 10)
	{
		BLKList.dequeue();
		//	Schedule(BlockedProcess, Processor);
	}
}

void Scheduler::WorkStealing()
{
	// get the shortest processor
	Processor* shortestProcessor = GetShortestProcessorWithoutRUN();

	// get the longest processor
	Processor* longestProcessor = GetLongestProcessorWithoutRUN();

	// if no processors are available, return
	if (shortestProcessor == nullptr || longestProcessor == nullptr)
	{
		return;
	}

	// calculate the stealing limit and check if it is more than the maximum stealing limit
	while (CalculateStealingLimit(longestProcessor, shortestProcessor) > MAX_STEALING_LIMIT)
	{
		Process* stolenProcess = longestProcessor->StealProcess();
		if (!stolenProcess) // No more processes to steal
			break;

		stolenProcess->SetStolen(true);					// set the stolen flag to true - (FOR STATS ONLY)
		Schedule(stolenProcess, shortestProcessor);		// move the stolen process to the shortest processor
	}

}

void Scheduler::OverHeating()
{
	// Get a random processor
	int randomProcessorIndex = (rand() % processors.GetLength()) + 1;

	Processor* randomProcessor = processors.GetEntry(randomProcessorIndex);

	if (randomProcessor->GetStatus() == STOP)
		return;

	// set the status of the random processor to STOP
	randomProcessor->SetStatus(STOP);
	randomProcessor->SetHeatingTime(simulationParameters.OVERHEAT_TIME);

	// Overheat the processor
	randomProcessor->OverHeat();
}


double Scheduler::CalculateStealingLimit(Processor* largestProcessor, Processor* smallestProcessor)
{
	// largest processor expected time
	double largestProcessorExpectedTime = largestProcessor->GetExpectedFinishTime();

	// smallest processor expected time
	double smallestProcessorExpectedTime = smallestProcessor->GetExpectedFinishTime();

	// calculate the stealing limit
	double stealingLimit = (largestProcessorExpectedTime - smallestProcessorExpectedTime) / (double)largestProcessorExpectedTime;

	return stealingLimit;
}

/// ////////////////////////////////// ///
///        Statistics Functions        ///
/// ////////////////////////////////// ///

std::string Scheduler::TRMListStatsToString()
{
	std::stringstream ss;

	unsigned int numOfTrmListProcess = TRMList.getSize();

	for (int i = 0; i < numOfTrmListProcess; i++)
	{
		Process* process = TRMList.peekFront();
		TRMList.dequeue();

		// Termination time (TT)
		ss << std::setfill('0') << std::setw(NUM_PRECISION) << process->GetTimeInfo().TT;
		ss << " ";

		// Process ID (PID)
		ss << std::setfill('0') << std::setw(NUM_PRECISION) << process->GetID();
		ss << " ";

		// Arrival Time (AT)
		ss << std::setfill('0') << std::setw(NUM_PRECISION) << process->GetTimeInfo().AT;
		ss << " ";

		// CPU Time (CT)
		ss << std::setfill('0') << std::setw(NUM_PRECISION) << process->GetTimeInfo().CT;
		ss << " ";

		// Total IO_Time Time (IO_D)
		ss << std::setfill('0') << std::setw(NUM_PRECISION) << process->GetTimeInfo().totalIOD;
		ss << " ";

		// Waiting Time (WT)
		ss << std::setfill('0') << std::setw(NUM_PRECISION) << process->GetTimeInfo().WT;
		ss << " ";

		// Response Time (RT)
		ss << std::setfill('0') << std::setw(NUM_PRECISION) << process->GetTimeInfo().RT;
		ss << " ";

		// Turnaround Time (TRT)
		ss << std::setfill('0') << std::setw(NUM_PRECISION) << process->GetTimeInfo().TRT;
		ss << " ";

		// end line
		ss << "\n";
		TRMList.enqueue(process);
	}


	return ss.str();
}

unsigned int Scheduler::CalculateAverageWaitTime()
{
	unsigned int totalWaitingTime = 0;

	for (int i = 0; i < TRMList.getSize(); i++)
	{
		Process* process = TRMList.peekFront();
		TRMList.dequeue();
		totalWaitingTime += process->GetTimeInfo().WT;
		TRMList.enqueue(process);
	}

	return totalWaitingTime / TRMList.getSize();
}

unsigned int Scheduler::CalculateTotalTurnaroundTime()
{
	unsigned int totalTurnaroundTime = 0;
	for (int i = 0; i < TRMList.getSize(); i++)
	{
		Process* process = TRMList.peekFront();
		TRMList.dequeue();
		totalTurnaroundTime += process->GetTimeInfo().TRT;
		TRMList.enqueue(process);
	}
	return totalTurnaroundTime;
}

unsigned int Scheduler::CalculateAverageTurnaroundTime()
{
	unsigned int totalTurnaroundTime = 0;
	for (int i = 0; i < TRMList.getSize(); i++)
	{
		Process* process = TRMList.peekFront();
		TRMList.dequeue();
		totalTurnaroundTime += process->GetTimeInfo().TRT;
		TRMList.enqueue(process);
	}
	return totalTurnaroundTime / TRMList.getSize();
}

unsigned int Scheduler::CalculateAverageResponseTime()
{
	unsigned int totalResponseTime = 0;

	for (int i = 0; i < TRMList.getSize(); i++)
	{
		Process* process = TRMList.peekFront();
		TRMList.dequeue();
		totalResponseTime += process->GetTimeInfo().RT;
		TRMList.enqueue(process);
	}

	return totalResponseTime / TRMList.getSize();
}

unsigned int* Scheduler::CalculateProcessorsUtilization()
{
	// get total turnaround time
	unsigned int totalCPUTime = clk->GetTime();
	unsigned int numOfProcessors = simulationParameters.N_FCFS + simulationParameters.N_RR + simulationParameters.N_SJF;

	// create array of processors utilization
	unsigned int* processorsUtilization = new unsigned int[numOfProcessors];

	// calculate utilization for each processor
	for (int i = 0; i < numOfProcessors; i++)
	{
		Processor* processor = processors.GetEntry(i + 1);
		processorsUtilization[i] = (processor->GetTotalBusyTime() / (double)totalCPUTime) * 100;
	}

	return processorsUtilization;
}

unsigned int* Scheduler::CalculateProcessorsLoad()
{
	// get total turnaround time
	unsigned int totalTurnaroundTime = CalculateTotalTurnaroundTime();
	unsigned int numOfProcessors = simulationParameters.N_FCFS + simulationParameters.N_RR + simulationParameters.N_SJF;

	// create array of processors load
	unsigned int* processorsLoad = new unsigned int[numOfProcessors];

	// calculate load for each processor
	for (int i = 0; i < numOfProcessors; i++)
	{
		Processor* processor = processors.GetEntry(i + 1);
		processorsLoad[i] = (processor->GetTotalBusyTime() / (double)totalTurnaroundTime) * 100;
	}

	return processorsLoad;
}

unsigned int Scheduler::CalculateAverageProcessorsUtilization()
{
	// get processors utilization
	unsigned int* processorsUtilization = CalculateProcessorsUtilization();

	// calculate average utilization
	unsigned int totalUtilization = 0;
	unsigned int numOfProcessors = simulationParameters.N_FCFS + simulationParameters.N_FCFS + simulationParameters.N_RR + simulationParameters.N_SJF;
	for (int i = 0; i < numOfProcessors; i++)
	{
		totalUtilization += processorsUtilization[i];
	}

	delete[] processorsUtilization;

	return totalUtilization / numOfProcessors;
}

unsigned int Scheduler::CaculateWorkStealPercent()
{
	// count stolen processes
	unsigned int numOfStolenProcesses = 0;
	for (int i = 0; i < TRMList.getSize(); i++)
	{
		Process* process = TRMList.peekFront();
		TRMList.dequeue();
		if (process->IsStolen())
		{
			numOfStolenProcesses++;
		}
		TRMList.enqueue(process);
	}

	return (numOfStolenProcesses / (double)TRMList.getSize()) * 100;
}

