#pragma once
#include "List.h"

template<class ItemType>
class ProcessorList : public List<ItemType>
{
private:
	Node<ItemType>* headPtr;	// Pointer to first node in the chain 
	int itemCount;				// Current count of list items

public:
	ProcessorList();
	ProcessorList(const ProcessorList<ItemType>& aList);
	virtual ~ProcessorList();

	Process* RemoveById(int id);
	void Clear();
};

template<class ItemType>
ProcessorList<ItemType>::ProcessorList() : headPtr(nullptr), itemCount(0)
{
}

template<class ItemType>
ProcessorList<ItemType>::ProcessorList(const ProcessorList<ItemType>& aList)
{
	if (!aList.isEmpty())
	{
		Node<ItemType>* outerListPtr = aList.headPtr;
		//create the first node
		headPtr = new Node<ItemType>;
		headPtr->setItem(outerListPtr->getItem());
		headPtr->setNext(nullptr);
		itemCount++;

		Node<ItemType>* innerListPtr = headPtr;
		outerListPtr = outerListPtr->getNext();

		while (outerListPtr != nullptr)
		{
			Node<ItemType>* newNodePtr = new Node<ItemType>;
			newNodePtr->setItem(outerListPtr->getItem());
			newNodePtr->setNext(nullptr);

			innerListPtr->setNext(newNodePtr);

			innerListPtr = innerListPtr->getNext();
			outerListPtr = outerListPtr->getNext();
			itemCount++;
		}
	}
}


template<class ItemType>
Process* ProcessorList<ItemType>::RemoveById(int id)
{
	Node<ItemType>* ptr = headPtr;
	Node<ItemType>* prv = nullptr;
	if (!ptr)
		return;
	while (ptr)
	{
		if (ptr->getItem() == id)
		{
			Node<T>* temp = ptr;
			if (!prv)
			{
				headPtr = ptr->getNext();
				ptr = headPtr;
			}
			else
			{
				prv->setNext(ptr->getNext());
				ptr = ptr->getNext();
			}
			temp->setNext(nullptr);
			itemCount--;

			return temp;
		}
		prv = ptr;
		ptr = ptr->getNext();
	}
	return nullptr;
}

template<class ItemType>
void ProcessorList<ItemType>::Clear()
{
	while (!IsEmpty())
		Remove(1);
} // end clear

template< class ItemType>
ProcessorList<ItemType>::~ProcessorList()
{
	Clear();
}