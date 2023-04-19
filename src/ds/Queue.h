#pragma once
///=///////////////////////////////////////////////////////////////////=///
/// QUEUE ADT: provides plain Abstract Data type for managing FIFO data ///
///=///////////////////////////////////////////////////////////////////=///
#include "Node.h"
#include <iostream>

template<class ItemType>
class Queue
{
private:
	// The queue is implemented as a chain of linked nodes that has
	// two external pointers, a head pointer for the front of the
	// queue and a tail pointer for the back of the queue.
	Node<ItemType>* backPtr;
	Node<ItemType>* frontPtr;
	unsigned int size;
public:
	Queue();
	Queue(const Queue& aQueue);
	virtual ~Queue();

	bool isEmpty() const;
	bool enqueue(const ItemType& newEntry);
	bool dequeue();
	unsigned int getSize() const;
	ItemType peekFront() const;
	std::string ToString();

	void operator = (const Queue& original);
};

template<class ItemType>
inline Queue<ItemType>::Queue()
	: backPtr(nullptr), frontPtr(nullptr), size(0)
{
}

template<class ItemType>
inline Queue<ItemType>::Queue(const Queue& aQueue) : frontPtr(nullptr), backPtr(nullptr), size(0)
{
	Node<ItemType>* originChainPtr = aQueue.frontPtr;

	if (originChainPtr == nullptr)
	{
		return;
	}

	while (originChainPtr != nullptr)
	{
		enqueue(originChainPtr->getItem());
		originChainPtr = originChainPtr->getNext();
	}
}

template<class ItemType>
inline Queue<ItemType>::~Queue()
{
	while (!isEmpty())
	{
		dequeue();
	}
}

template<class ItemType>
inline bool Queue<ItemType>::isEmpty() const
{
	return frontPtr == nullptr;
}

template<class ItemType>
inline bool Queue<ItemType>::enqueue(const ItemType& newEntry)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
	size++;


	if (isEmpty())
		frontPtr = newNodePtr;
	else
		backPtr->setNext(newNodePtr);
	backPtr = newNodePtr;
	return true;
}

template<class ItemType>
inline bool Queue<ItemType>::dequeue()
{
	bool result = false;

	if (!isEmpty())
	{
		// Queue is not empty: remove front
		Node<ItemType>* nodeToDeletePtr = frontPtr;
		size--;

		if (frontPtr == backPtr) // Special case: one node in queue
		{
			frontPtr = nullptr;
			backPtr = nullptr;
		}
		else
			frontPtr = frontPtr->getNext();

		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		result = true;
	}
	return result;
}

template<class ItemType>
inline unsigned int Queue<ItemType>::getSize() const
{
	return size;
}

template<class ItemType>
inline ItemType Queue<ItemType>::peekFront() const
{
	return frontPtr->getItem();	// didn't check for empty because it's in the specification as a @pre
}

template<class ItemType>
inline std::string Queue<ItemType>::ToString()
{
	std::string str = "";
	Node<ItemType>* curPtr = frontPtr;
	while (curPtr)
	{
		str += curPtr->getItem()->ToString();

		if (curPtr->getNext())
		{
			str += ", ";
		}

		curPtr = curPtr->getNext();
	}

	if (isEmpty())
	{
		str += "Empty List";
	}
	return str;
}

template<class ItemType>
void Queue<ItemType>::operator = (const Queue<ItemType>& aQueue)
{
	Node<ItemType>* originChainPtr = aQueue.frontPtr;

	while (originChainPtr != nullptr)
	{
		enqueue(originChainPtr->getItem());
		originChainPtr = originChainPtr->getNext();
	}
}