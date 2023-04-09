#pragma once

#include "Node.h"

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
	Node<ItemType>* getNodeAt(int position) const;

public:
	List();
	List(const List<ItemType>& aList);
	virtual ~List();

	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const ItemType& newEntry);
	bool remove(int position);
	void clear();

	ItemType getEntry(int position) const;
	void setEntry(int position, const ItemType& newEntry);
};

