#include "Scheduler.h"

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
		std::cout << std::endl;
	}
}

void Scheduler::PrintTRMList()
{
}

void Scheduler::PrintBLKList()
{
}

void Scheduler::PrintRUNList()
{
}
