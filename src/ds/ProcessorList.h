#pragma once
#include "List.h"

template<class ItemType>
class ProcessorList : public List<ItemType>
{
private:
	Node<ItemType>* headPtr;	// Pointer to first node in the chain 
	int itemCount;				// Current count of list items

	Node<ItemType>* GetNodeAt(int position) const;
public:
	ProcessorList();
	ProcessorList(const ProcessorList<ItemType>& aList);
	virtual ~ProcessorList();

	Process* RemoveById(int id);
	bool Remove(int position);
	bool IsEmpty() const;
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
Node<ItemType>* ProcessorList<ItemType>::GetNodeAt(int position) const
{
	if (position > itemCount || position < 1)
		return nullptr;
	// Count from the beginning of the chain 
	Node<ItemType>* curPtr = headPtr;
	for (int skip = 1; skip < position; skip++)
		curPtr = curPtr->getNext();
	return curPtr;
} // end getNodeAt 


template<class ItemType>
bool ProcessorList<ItemType>::IsEmpty() const
{
	return (itemCount == 0);
}

template<class ItemType>
ItemType* ProcessorList<ItemType>::RemoveById(int id)
{
	Node<ItemType>* ptr = headPtr;
	Node<ItemType>* prv = nullptr;
	while (ptr)
	{
		if (ptr->getItem() == id)
		{
			Node<ItemType>* temp = ptr;
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
bool ProcessorList<ItemType>::Remove(int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		Node<ItemType>* curPtr = nullptr;
		if (position == 1)
		{
			// Remove the first node in the chain 
			curPtr = headPtr; // Save pointer to node 
			headPtr = headPtr->getNext();
		}
		else
		{
			// Find node that is before the one to delete 
			Node<ItemType>* prevPtr = GetNodeAt(position - 1);
			// Point to node to delete 
			curPtr = prevPtr->getNext();
			// Disconnect indicated node from chain by connecting the 
			 // prior node with the one after 
			prevPtr->setNext(curPtr->getNext());
		} // end if 
	   // Return node to system 
		curPtr->setNext(nullptr);
		delete curPtr;
		curPtr = nullptr;
		itemCount--; // Decrease count of entries 
	} // end if 
	return ableToRemove;
} // end remove

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