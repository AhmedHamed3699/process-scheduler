#pragma once

template<class ItemType>
class Node
{
private:
	ItemType item;
	Node<ItemType>* next;
public:
	Node();
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
	void setItem(const ItemType& anItem);
	void setNext(Node<ItemType>* nextNodePtr);
	ItemType getItem() const;
	Node<ItemType>* getNext() const;
};

template<class ItemType>
inline Node<ItemType>::Node()
	: next(nullptr)
{
}

template<class ItemType>
inline Node<ItemType>::Node(const ItemType& anItem)
	: item(anItem), next(nullptr)
{
}

template<class ItemType>
inline Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr)
	: item(anItem), next(nextNodePtr)
{
}

template<class ItemType>
inline void Node<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
}

template<class ItemType>
inline void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
	next = nextNodePtr;
}

template<class ItemType>
inline ItemType Node<ItemType>::getItem() const
{
	return item;
}

template<class ItemType>
inline Node<ItemType>* Node<ItemType>::getNext() const
{
	return next;
}