#pragma once
#include <iostream>
#include <type_traits>
using namespace std;

template<class ItemType>
class PriorityQueue
{
private:
	static const int DEFAULT_CAPACITY = 100;
	ItemType* items;
	int itemCount;
	int maxItems;
	int left(const int nodeIndex) const;
	int right(int nodeIndex) const;
	int parent(int nodeIndex) const;
	bool isLower(const ItemType& a, const ItemType& b) const;
	void minHeapify(int nodeIndex);
	void buildHeap();
public:
	PriorityQueue();
	PriorityQueue(const ItemType someArray[], const int arraySize);
	PriorityQueue(const PriorityQueue& H);
	bool isEmpty() const;
	ItemType peekFront() const;
	bool enqueue(const ItemType& newData);
	bool dequeue();
	bool dequeue(ItemType& min);
	int getSize() const;
	void clear();
	void Print(); // for UI
	virtual ~PriorityQueue();
};

template<class ItemType>
PriorityQueue<ItemType>::PriorityQueue() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
	items = new ItemType[DEFAULT_CAPACITY];
}

template<class ItemType>
PriorityQueue<ItemType>::PriorityQueue(const ItemType someArray[], const int arraySize)
{
	itemCount = arraySize;
	maxItems = max(arraySize, DEFAULT_CAPACITY);
	items = new ItemType[arraySize];

	for (int i = 0; i < arraySize; i++)
		items[i] = someArray[i];

	buildHeap();
}

template<class ItemType>
PriorityQueue<ItemType>::PriorityQueue(const PriorityQueue& H)
{
	itemCount = H.itemCount;
	maxItems = H.maxItems;
	items = new ItemType[itemCount];

	for (int i = 0; i < itemCount; i++)
		items[i] = H.items[i];
}

template<class ItemType>
PriorityQueue<ItemType>::~PriorityQueue()
{
	itemCount = 0;
	maxItems = DEFAULT_CAPACITY;
	delete[] items;
}

template<class ItemType>
int PriorityQueue<ItemType>::left(const int nodeIndex) const
{
	return (2 * nodeIndex) + 1;
}

template<class ItemType>
int PriorityQueue<ItemType>::right(int nodeIndex) const
{
	return 2 * (nodeIndex + 1);
}

template<class ItemType>
int PriorityQueue<ItemType>::parent(int nodeIndex) const
{
	return (nodeIndex - 1) / 2;
}

template<class ItemType>
bool PriorityQueue<ItemType>::isLower(const ItemType& a, const ItemType& b) const
{
	if (is_pointer<ItemType>::value)
		return (*a < b);
	return (a < b);
}

template<class ItemType>
void PriorityQueue<ItemType>::minHeapify(int nodeIndex)
{
	int l = left(nodeIndex);
	int r = right(nodeIndex);
	int smallest = nodeIndex;

	if (l < itemCount && isLower(items[l], items[smallest]))
		smallest = l;
	if (r < itemCount && isLower(items[r], items[smallest]))
		smallest = r;
	if (smallest != nodeIndex)
	{
		swap(items[smallest], items[nodeIndex]);
		minHeapify(smallest);
	}
}

template<class ItemType>
void PriorityQueue<ItemType>::buildHeap()
{
	for (int i = itemCount / 2; i >= 0; i--)
		minHeapify(i);
}

template<class ItemType>
bool PriorityQueue<ItemType>::isEmpty() const
{
	return (itemCount == 0);
}

template<class ItemType>
ItemType PriorityQueue<ItemType>::peekFront() const
{
	return items[0];
}

template<class ItemType>
bool PriorityQueue<ItemType>::enqueue(const ItemType& newData)
{
	if (itemCount == maxItems)
	{
		ItemType* temp = new ItemType[2 * maxItems];
		if (temp == nullptr)
			return false;

		for (int i = 0; i < itemCount; i++) {
			temp[i] = items[i];
		}

		delete[] items;
		maxItems *= 2;
		items = temp;
	}

	int i = itemCount;
	items[itemCount++] = newData;
	while (i > 0)
	{
		int p = parent(i);
		if (!isLower(items[i], items[p]))
			break;

		swap(items[i], items[p]);
		i = parent(i);
	}
	return true;
}

template<class ItemType>
bool PriorityQueue<ItemType>::dequeue()
{
	if (isEmpty())
		return false;

	items[0] = items[--itemCount];
	minHeapify(0);
	return true;
}

template<class ItemType>
bool PriorityQueue<ItemType>::dequeue(ItemType& min)
{
	if (isEmpty())
		return false;

	min = items[0];
	items[0] = items[--itemCount];
	minHeapify(0);
	return true;
}

template<class ItemType>
inline int PriorityQueue<ItemType>::getSize() const
{
	return itemCount;
}

template<class ItemType>
void PriorityQueue<ItemType>::clear()
{
	itemCount = 0;
	maxItems = DEFAULT_CAPACITY;
	delete[] items;
	items = new ItemType[DEFAULT_CAPACITY];
}

template<class ItemType>
inline void PriorityQueue<ItemType>::Print()
{
	for (int i = 0; i < itemCount; i++)
	{
		items[i]->Print();
		if (i != itemCount - 1)
		{
			std::cout << ", ";
		}
	}

	if (itemCount == 0)
	{
		std::cout << "Empty List";
	}
}
