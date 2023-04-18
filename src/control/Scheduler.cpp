#include "Scheduler.h"
#include <cstdlib>

/// ////////////////////////////////// ///
///    constructors and destructor     ///
/// ////////////////////////////////// ///
Scheduler::Scheduler()
	:simulationParameters(0, 0, 0, 0, 0, 0, 0, 0, 0),
	IOProcess(nullptr)
{
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
	// create new processor
	Process* newProcess = new Process(id);
	newProcess->SetStatus(NEW);
	// add processor to the NEW list
	NEWList.enqueue(newProcess);
}

void Scheduler::CreateNewProcess(int AT, int PID, int CT)
{
	// create new processor
	Process* newProcess = new Process(PID);
	newProcess->SetStatus(NEW);

	TimeInfo timeInfo;
	timeInfo.AT = AT;
	timeInfo.CT = CT;
	timeInfo.RCT = CT;

	newProcess->SetTimeInfo(timeInfo);

	// add processor to the NEW list
	NEWList.enqueue(newProcess);
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
	// this means we must change N_PROCESS when we fork .. or terminate the program in another way

	return (simulationParameters.N_PROCESS == TRMList.getSize());
}

/// ////////////////////////////////// ///
///           UI AID Functions         ///
/// ////////////////////////////////// ///
void Scheduler::PrintRDYLists()
{
	for (int i = 1; i <= processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i);
		std::cout << "Processor " << i << " ";
		processor->Print();
	}
}

void Scheduler::PrintTRMList()
{
	std::cout << TRMList.getSize() << " TRM: ";
	TRMList.Print();
	std::cout << std::endl;
}

void Scheduler::PrintBLKList()
{
	std::cout << BLKList.getSize() << " BLK: ";
	BLKList.Print();
	std::cout << std::endl;
}

void Scheduler::PrintRUNList()
{
	string* RUNList = new string[processors.GetLength()];
	unsigned int runListSize = 0;

	for (int i = 1; i <= processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i);
		if (processor->GetCurrentProcess() != nullptr)
		{
			RUNList[runListSize++] = to_string(processor->GetCurrentProcess()->GetID()) + "(P" + to_string(i) + ")";
		}
	}


	std::cout << runListSize << " RUN: ";
	for (unsigned int i = 0; i < runListSize; i++)
	{
		std::cout << RUNList[i];
		if (i < runListSize - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}

/// ////////////////////////////////// ///
///     Process State Management       ///
/// ////////////////////////////////// ///
void Scheduler::ScheduleNext(int currentTime)
{
	while (!NEWList.isEmpty())
	{
		Process* process = NEWList.peekFront();

		TimeInfo timeInfo = process->GetTimeInfo();
		if (timeInfo.AT != currentTime)
			return;

		NEWList.dequeue();

		/// TODO: implement the scheduling algorithm (Phase 2)

		// get the next processor
		Processor* processor = processors.GetEntry(nextProcessorIndex + 1);
		nextProcessorIndex = (nextProcessorIndex + 1) % processors.GetLength();

		// schedule the process
		processor->AddProcessToList(process);
	}
}

void Scheduler::ScheduleNextFCFS(Process* process)
{
}

void Scheduler::ScheduleNextSJF(Process* process)
{
}

void Scheduler::ScheduleNextRR(Process* process)
{
}

void Scheduler::TerminateProcess(Process* process)
{
	if (process->GetStatus() == TRM)
	{
		return;
	}
	process->SetStatus(TRM);
	TRMList.enqueue(process);
}

void Scheduler::BlockProcess(Process* process)
{
	if (process->GetStatus() == BLK)
	{
		return;
	}

	process->SetStatus(BLK);
	BLKList.enqueue(process);
}

/// ////////////////////////////////// ///
///        Simulation Functions        ///
/// ////////////////////////////////// ///

void Scheduler::RunProcesses(int CurrentTime)
{
	for (int i = 0; i < processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i + 1);
		if(processor->GetStatus() == IDLE)
		{
			processor->ExecuteProcess(CurrentTime);
		}
		
	}
}

void Scheduler::MoveToRDY(Process* process)
{
	// get the next processor
	Processor* processor = processors.GetEntry(nextProcessorIndex + 1);
	nextProcessorIndex = (nextProcessorIndex + 1) % processors.GetLength();

	// schedule the process
	processor->AddProcessToList(process);
}

void Scheduler::MoveFromRun(int CurrentTime)
{
	for (int i = 0; i < processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i + 1);
		Process* CurrentProcess = processor->GetCurrentProcess();
		if (CurrentProcess == nullptr)
			continue;

		TimeInfo timeInfo = CurrentProcess->GetTimeInfo();

		if(timeInfo.RT + timeInfo.AT == CurrentTime)
			continue;

		int probability = (rand() % 100) + 1;
		if (probability <= 15)
		{
			processor->SetStatus(IDLE);
			processor->SetCurrentProcess(nullptr);
			BlockProcess(CurrentProcess);

			TimeInfo timeInfo = CurrentProcess->GetTimeInfo();
			timeInfo.BT = CurrentTime;
			CurrentProcess->SetTimeInfo(timeInfo);
		}
		else if (probability >= 20 && probability <= 30)
		{
			processor->SetStatus(IDLE);
			processor->SetCurrentProcess(nullptr);
			MoveToRDY(CurrentProcess);
		}
		else if (probability >= 50 && probability <= 60)
		{
			processor->SetStatus(IDLE);
			processor->SetCurrentProcess(nullptr);
			TerminateProcess(CurrentProcess);
		}
	}
}

void Scheduler::MoveFromBLK(int CurrentTime)
{
	int probability = (rand() % 100) + 1;
	if (BLKList.isEmpty())
		return;

	Process* BlockedProcess = BLKList.peekFront();

	if (BlockedProcess->GetTimeInfo().BT == CurrentTime)
		return;

	if (probability < 10)
	{
		BLKList.dequeue();
		MoveToRDY(BlockedProcess);
	}
}

void Scheduler::SimulateKill()
{
	int RandID = rand() % 31;
	for (int i = 0; i < simulationParameters.N_FCFS; i++)
	{
		Processor* processor = processors.GetEntry(i + 1);
		bool found = processor->KillProcessHandler(RandID);

		if (found)
			return;
	}
}

/// ////////////////////////////////// ///
///        Statistics Functions        ///
/// ////////////////////////////////// ///

unsigned int Scheduler::CalculateAverageWaitTime()
{
	return 0;
}

unsigned int Scheduler::CalculateAverageTurnaroundTime()
{
	return 0;
}

unsigned int Scheduler::CalculateAverageResponseTime()
{
	return 0;
}

unsigned int* Scheduler::CalculateProcessorsUtilization()
{
	return nullptr;
}

unsigned int* Scheduler::CalculateProcessorsLoad()
{
	return nullptr;
}

unsigned int Scheduler::CalculateAverageProcessorsUtilization()
{
	return 0;
}

