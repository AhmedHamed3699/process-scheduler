#pragma once

#include "List.h"

template<class ItemType>
class FCFSList : public List<ItemType>
{
public:
	FCFSList();
	FCFSList(const FCFSList<ItemType>& aList);
	virtual ~FCFSList();

	Process* RemoveById(int id);
};

template<class ItemType>
FCFSList<ItemType>::FCFSList() : headPtr(nullptr), tailPtr(nullptr), itemCount(0)
{
}

template<class ItemType>
FCFSList<ItemType>::FCFSList(const FCFSList<ItemType>& aList) : headPtr(nullptr), tailPtr(nullptr), itemCount(0)
{
	if (!aList.IsEmpty())
	{
		Node<ItemType>* outerListPtr = aList.headPtr;
		//create the first node
		headPtr = new Node<ItemType>;
		headPtr->setItem(outerListPtr->getItem());
		headPtr->setNext(nullptr);
		tailPtr = headPtr;
		itemCount++;

		outerListPtr = outerListPtr->getNext();

		while (outerListPtr != nullptr)
		{
			Node<ItemType>* newNodePtr = new Node<ItemType>;
			newNodePtr->setItem(outerListPtr->getItem());
			newNodePtr->setNext(nullptr);

			tailPtr->setNext(newNodePtr);

			tailPtr = tailPtr->getNext();
			outerListPtr = outerListPtr->getNext();
			itemCount++;
		}
	}
}

template<class ItemType>
Process* FCFSList<ItemType>::RemoveById(int id)
{
	Node<Process*>* ptr = headPtr;
	Node<Process*>* prv = nullptr;
	while (ptr)
	{
		if (*(ptr->getItem()) == id)
		{
			Node<Process*>* temp = ptr;
			if (!prv)	//if the NodeToBeDeleted is the first node
			{
				headPtr = ptr->getNext();
				ptr = headPtr;

				if (itemCount == 1)		//only one node exist in the list
				{
					tailPtr = nullptr;
				}
			}
			else
			{
				prv->setNext(ptr->getNext());

				if (ptr->getNext() == nullptr)		//if the NodeToBeDeleted is the last node
				{
					tailPtr = prv;
				}

				ptr = ptr->getNext();
			}
			temp->setNext(nullptr);
			Process* RemovedOne = temp->getItem();
			delete temp;
			itemCount--;

			return RemovedOne;
		}
		prv = ptr;
		ptr = ptr->getNext();
	}
	return nullptr;
}

template< class ItemType>
FCFSList<ItemType>::~FCFSList()
{
	Clear();
}