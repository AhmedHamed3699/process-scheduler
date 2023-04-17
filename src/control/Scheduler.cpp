#include "Scheduler.h"

/// ////////////////////////////////// ///
///    constructors and destructor     ///
/// ////////////////////////////////// ///
Scheduler::Scheduler()
	:simulationParameters(0, 0, 0, 0, 0, 0, 0, 0, 0),
	IOProcess(nullptr)
{
}

Scheduler::Scheduler(unsigned int maxW, unsigned int RRTS, 
	unsigned int numFCFS, unsigned int numSJF, unsigned int numRR, 
	unsigned int fP, unsigned int STL, unsigned int RTF,
	unsigned int numProcess):simulationParameters(maxW, RRTS, numFCFS, numSJF, numRR, fP, STL, RTF, numProcess),
	IOProcess(nullptr)
{
}

/// ////////////////////////////////// ///
///         Creation and setup         ///
/// ////////////////////////////////// ///
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
	// add processor to the NEW list
	NEWList.enqueue(newProcess);
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
void Scheduler::ScheduleNext()
{
	if (NEWList.isEmpty())
	{
		return;
	}

	Process* process = NEWList.peekFront();
	NEWList.dequeue();

	/// TODO: implement the scheduling algorithm

	// get the next processor
	Processor* processor = processors.GetEntry(nextProcessorIndex + 1);
	nextProcessorIndex = (nextProcessorIndex + 1) % processors.GetLength();

	// schedule the process
	processor->AddProcessToList(process);
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
	/// TODO: remove later
	if (NEWList.isEmpty())
	{
		return;
	}
	process = NEWList.peekFront();
	NEWList.dequeue();


	TRMList.enqueue(process);
}

void Scheduler::BlockProcess(Process* process)
{
	/// TODO: remove later
	if (NEWList.isEmpty())
	{
		return;
	}
	process = NEWList.peekFront();
	NEWList.dequeue();


	BLKList.enqueue(process);

}

/// TODO: remove this later
void Scheduler::RunProcesses()
{
	for (int i = 0; i < processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i + 1);
		processor->ExecuteProcess();
	}
}
