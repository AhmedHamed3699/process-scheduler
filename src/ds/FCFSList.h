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
FCFSList<ItemType>::FCFSList() : List()
{
}

template<class ItemType>
FCFSList<ItemType>::FCFSList(const FCFSList<ItemType>& aList) : List()
{
	if (!aList.IsEmpty())
	{
		Node<ItemType>* outerListPtr = aList.headPtr;
		//create the first node
		this->headPtr = new Node<ItemType>;
		this->headPtr->setItem(outerListPtr->getItem());
		this->headPtr->setNext(nullptr);
		this->tailPtr = this->headPtr;
		this->itemCount++;

		outerListPtr = outerListPtr->getNext();

		while (outerListPtr != nullptr)
		{
			Node<ItemType>* newNodePtr = new Node<ItemType>;
			newNodePtr->setItem(outerListPtr->getItem());
			newNodePtr->setNext(nullptr);

			this->tailPtr->setNext(newNodePtr);

			this->tailPtr = this->tailPtr->getNext();
			outerListPtr = outerListPtr->getNext();
			this->itemCount++;
		}
	}
}

template<class ItemType>
Process* FCFSList<ItemType>::RemoveById(int id)
{
	Node<Process*>* ptr = this->headPtr;
	Node<Process*>* prv = nullptr;
	while (ptr)
	{
		if (*(ptr->getItem()) == id)
		{
			Node<Process*>* temp = ptr;
			if (!prv)	//if the NodeToBeDeleted is the first node
			{
				this->headPtr = ptr->getNext();
				ptr = this->headPtr;

				if (this->itemCount == 1)		//only one node exist in the list
				{
					this->tailPtr = nullptr;
				}
			}
			else
			{
				prv->setNext(ptr->getNext());

				if (ptr->getNext() == nullptr)		//if the NodeToBeDeleted is the last node
				{
					this->tailPtr = prv;
				}

				ptr = ptr->getNext();
			}
			temp->setNext(nullptr);
			Process* RemovedOne = temp->getItem();
			delete temp;
			this->itemCount--;

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
	this->Clear();
}