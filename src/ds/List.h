#pragma once

#include "Node.h"
#include <iostream> // for UI Print

template<class ItemType>
class List
{
private:
	Node<ItemType>* headPtr;	// Pointer to first node in the chain 
	// (contains the first entry in the list) 
	int itemCount;				// Current count of list items

	// Locates a specified node in a linked list. 
	// @pre position is the number of the desired node; 
	// position >= 1 and position <= itemCount. 
	// @post The node is found and a pointer to it is returned. 
	// @param position The number of the node to locate. 
	// @return A pointer to the node at the given position. 
	Node<ItemType>* GetNodeAt(int position) const;

public:
	List();
	List(const List<ItemType>& aList);
	virtual ~List();

	bool IsEmpty() const;
	int GetLength() const;
	bool Insert(int newPosition, const ItemType& newEntry);
	bool Remove(int position);
	void Clear();

	void Print(); // made for ui

	/** position must be >= 1 && position <= itemCount */
	ItemType GetEntry(int position) const;
	void SetEntry(int position, const ItemType& newEntry);
};

template<class ItemType>
List<ItemType>::List() : headPtr(nullptr), itemCount(0)
{
}

template<class ItemType>
List<ItemType>::List(const List<ItemType>& aList)
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
Node<ItemType>* List<ItemType>::GetNodeAt(int position) const
{
	// Count from the beginning of the chain 
	Node<ItemType>* curPtr = headPtr;
	for (int skip = 1; skip < position; skip++)
		curPtr = curPtr->getNext();
	return curPtr;
} // end getNodeAt 

template<class ItemType>
bool List<ItemType>::IsEmpty() const
{
	return (itemCount == 0);
}

template<class ItemType>
int List<ItemType>::GetLength() const
{
	return itemCount;
}

template<class ItemType>
bool List<ItemType>::Insert(int newPosition,
	const ItemType& newEntry)
{
	bool ableToInsert = (newPosition >= 1) &&
		(newPosition <= itemCount + 1);
	if (ableToInsert)
	{
		// Create a new node containing the new entry
		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
		// Attach new node to chain 
		if (newPosition == 1)
		{
			// Insert new node at beginning of chain 
			newNodePtr->setNext(headPtr);
			headPtr = newNodePtr;
		}
		else
		{
			// Find node that will be before new node 
			Node<ItemType>* prevPtr = GetNodeAt(newPosition - 1);
			// Insert new node after node to which prevPtr points 
			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
		} // end if 
		itemCount++; // Increase count of entries 
	} // end if 
	return ableToInsert;
} // end insert 


template<class ItemType>
bool List<ItemType>::Remove(int position)
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
void List<ItemType>::Clear()
{
	while (!IsEmpty())
		Remove(1);
} // end clear

template<class ItemType>
inline void List<ItemType>::Print()
{
	Node<ItemType>* curPtr = headPtr;
	while (curPtr)
	{
		curPtr->getItem()->Print();

		if (curPtr->getNext())
		{
			std::cout << ", ";
		}

		curPtr = curPtr->getNext();
	}

	if (itemCount == 0)
	{
		std::cout << "Empty List";
	}
}

template<class ItemType>
ItemType List<ItemType>::GetEntry(int position) const
{
	// Enforce precondition 
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		Node<ItemType>* nodePtr = GetNodeAt(position);
		return nodePtr->getItem();
	}
}

template<class ItemType>
void List<ItemType>::SetEntry(int position, const ItemType& newEntry)
{
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		Node<ItemType>* nodePtr = GetNodeAt(position);
		nodePtr->setItem(newEntry);
	}
}

template< class ItemType>
List<ItemType>::~List()
{
	Clear();
} // end destructor 