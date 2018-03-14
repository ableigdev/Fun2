#pragma once

#include "ReadAccessViolation.h"

template <typename NODETYPE> class ListIterator;

template <class NODETYPE>
class List
{
	friend ListIterator<NODETYPE>;
public:
	List(); 
	List(const List<NODETYPE>&);
	~List();

	void pushFront(const NODETYPE&);
	void pushBack(const NODETYPE&);
	void pushInSortList(const NODETYPE&);

	void setCurrentNodeOnTheBegin();

	bool deleteElement(NODETYPE);
	void deleteAllElements();

	bool findValue(const NODETYPE&);

	bool isEmpty() const;
	void print() const;

	void sort();

	bool operator!() const;
	const List<NODETYPE>& operator=(const List<NODETYPE>&);
	List<NODETYPE>& operator++();
	List<NODETYPE>& operator--();

	const NODETYPE& getReferencesCurrentData() const;
	NODETYPE getValueCurrentData() const;

private:
	template <typename NODETYPE>
	struct ListNode
	{
		NODETYPE data; 
		ListNode<NODETYPE>* nextPtr = 0;
		ListNode<NODETYPE>* prevPtr = 0;
	};
						
	ListNode<NODETYPE>* firstPtr;
	ListNode<NODETYPE>* currentNodePtr;

private:
	void copyList(ListNode<NODETYPE>*);
	void deleteRemaindList(ListNode<NODETYPE>*);
};

template <typename NODETYPE>
List<NODETYPE>::List()
	: firstPtr(0),
	currentNodePtr(0)
{
	
}

template <typename NODETYPE>
List<NODETYPE>::List(const List<NODETYPE>& rList)
{
	firstPtr = 0;
	currentNodePtr = 0;

	if (!rList)
	{
		*this = rList;
	}
}

template <typename NODETYPE>
List<NODETYPE>::~List()
{
	deleteAllElements();
}

template <typename NODETYPE>
const List<NODETYPE>& List<NODETYPE>::operator=(const List<NODETYPE>& rList)
{
	if (this != &rList)
	{
		copyList(rList.firstPtr);
	}

	return *this;
}

template <typename NODETYPE>
bool List<NODETYPE>::operator!() const
{
	return !isEmpty();
}

template <typename NODETYPE>
List<NODETYPE>& List<NODETYPE>::operator++()
{
	if (currentNodePtr == 0)
		throw ReadAccessViolation();
	
	currentNodePtr = currentNodePtr->nextPtr;

	if (currentNodePtr == firstPtr)
	{
		return nullptr;
	}
	else
	{
		return *this;
	}
}

template <typename NODETYPE>
List<NODETYPE>& List<NODETYPE>::operator--()
{
	if (currentNodePtr == 0)
		throw ReadAccessViolation();
	
	currentNodePtr = currentNodePtr->prevPtr;

	if (currentNodePtr == firstPtr)
	{
		return nullptr;
	}
	else
	{
		return *this;
	}
}

template <typename NODETYPE>
bool List<NODETYPE>::isEmpty() const
{
	return firstPtr == 0;
}

template <typename NODETYPE>
void List<NODETYPE>::setCurrentNodeOnTheBegin()
{
	currentNodePtr = firstPtr;
}

template <typename NODETYPE>
void List<NODETYPE>::copyList(ListNode<NODETYPE>* rightPtr)
{
	if (rightPtr != 0)
	{
		ListNode<NODETYPE>* currentFirstPtr = firstPtr;
		ListNode<NODETYPE>* currentRightPtr = rightPtr;
		int counter = 0;

		do
		{
			if (currentFirstPtr == 0 || counter != 0 && currentFirstPtr == firstPtr)
			{
				pushBack(currentRightPtr->data);
			}
			else
			{
				currentFirstPtr->data = currentRightPtr->data;
				currentFirstPtr = currentFirstPtr->nextPtr;
				++counter;
			}
			
			currentRightPtr = currentRightPtr->nextPtr;
			
		} while (currentRightPtr != rightPtr);

		if (currentFirstPtr != firstPtr)
		{
			deleteRemaindList(currentFirstPtr);
		}
	}
}

template <typename NODETYPE>
void List<NODETYPE>::deleteRemaindList(ListNode<NODETYPE>* ptr)
{
	if (ptr != 0)
	{
		ListNode<NODETYPE>* tempPtr = 0;
		do
		{
			ptr->prevPtr->nextPtr = ptr->nextPtr;
			ptr->nextPtr->prevPtr = ptr->prevPtr;

			tempPtr = ptr;
			ptr = ptr->nextPtr;
			delete tempPtr;
		} while (ptr != firstPtr);
	}
}

template <typename NODETYPE>
void List<NODETYPE>::print() const
{
	if (!isEmpty())
	{
		ListNode<NODETYPE>* currentPtr = firstPtr;

		do
		{
			std::cout << currentPtr->data << ' ';
			currentPtr = currentPtr->nextPtr;
		} while (currentPtr != firstPtr);
	}
	std::cout << std::endl;
}

template <typename NODETYPE>
void List<NODETYPE>::pushFront(const NODETYPE& value)
{
	ListNode<NODETYPE>* newPtr = new ListNode<NODETYPE>;
	newPtr->data = value;

	if (isEmpty())
	{	
		firstPtr->nextPtr = firstPtr->prevPtr = firstPtr = newPtr;
	}
	else
	{
		ListNode<NODETYPE>* tempPtr = firstPtr->prevPtr;
		newPtr->nextPtr = firstPtr;
		newPtr->prevPtr = firstPtr->prevPtr;
		firstPtr->prevPtr = newPtr;
		tempPtr->nextPtr = newPtr;
		firstPtr = newPtr;
	}
	currentNodePtr = firstPtr;
}

template <typename NODETYPE>
void List<NODETYPE>::pushBack(const NODETYPE& value)
{
	ListNode<NODETYPE>* newPtr = new ListNode<NODETYPE>;
	newPtr->data = value;

	if (isEmpty())
	{
		firstPtr->nextPtr = firstPtr->prevPtr = firstPtr = newPtr;
	}
	else
	{
		ListNode<NODETYPE>* tempPtr = firstPtr->prevPtr;
		newPtr->nextPtr = firstPtr;
		newPtr->prevPtr = firstPtr->prevPtr;
		firstPtr->prevPtr = newPtr;
		tempPtr->nextPtr = newPtr;
	}
	currentNodePtr = firstPtr;
}

template <typename NODETYPE>
void List<NODETYPE>::pushInSortList(const NODETYPE& value)
{
	if (isEmpty() || value <= firstPtr->data)
	{
		pushFront(value);
	}
	else if (value >= firstPtr->prevPtr->data)
	{
		pushBack(value);
	}
	else
	{
		ListNode<NODETYPE>* newPtr = new ListNode<NODETYPE>;
		newPtr->data = value;

		ListNode<NODETYPE>* currentPtr = firstPtr;

		do
		{
			if (newPtr->data <= currentPtr->data)
			{
				ListNode<NODETYPE>* tempPtr = currentPtr->prevPtr;
				tempPtr->nextPtr = newPtr;
				newPtr->prevPtr = tempPtr;
				newPtr->nextPtr = currentPtr;
				currentPtr->prevPtr = newPtr;
				return;
			}
			currentPtr = currentPtr->nextPtr;
		} while (currentPtr != firstPtr);
	}
}

template <typename NODETYPE>
bool List<NODETYPE>::deleteElement(NODETYPE value)
{
	if (!isEmpty())
	{
		ListNode<NODETYPE>* currentPtr = firstPtr;
		ListNode<NODETYPE>* tempPtr = 0;

		do
		{
			if (currentPtr->data == value)
			{
				ListNode<NODETYPE>* prevTempPtr = currentPtr->prevPtr;
				ListNode<NODETYPE>* nextTempPtr = currentPtr->nextPtr;
				tempPtr = currentPtr;

				prevTempPtr->nextPtr = nextTempPtr;
				nextTempPtr->prevPtr = prevTempPtr;

				delete tempPtr;

				if (currentPtr == firstPtr)
				{
					firstPtr = nextTempPtr;
				}

				return true;
			}
			currentPtr = currentPtr->nextPtr;
		} while (currentPtr != firstPtr);
	}
	return false;
}

template <typename NODETYPE>
void List<NODETYPE>::deleteAllElements()
{
	if (!isEmpty())
	{
		ListNode<NODETYPE>* currentPtr = firstPtr;
		ListNode<NODETYPE>* tempPtr;

		do
		{
			tempPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
			delete tempPtr;
		} while (currentPtr != firstPtr);
	}
}

template <typename NODETYPE>
bool List<NODETYPE>::findValue(const NODETYPE& value)
{
	if (!isEmpty())
	{
		ListNode<NODETYPE>* currentPtr = firstPtr;

		do
		{
			if (value == currentPtr->data)
			{
				return true;
			}
			currentPtr = currentPtr->nextPtr;
		} while (currentPtr != firstPtr);
	}
	return false;
}

template <typename NODETYPE>
const NODETYPE& List<NODETYPE>::getReferencesCurrentData() const
{
	if (currentNodePtr != nullptr)
	{
		return currentNodePtr->data;
	}
	else
	{
		return 0;
	}
}

template <typename NODETYPE>
NODETYPE List<NODETYPE>::getValueCurrentData() const
{
	if (currentNodePtr != nullptr)
	{
		return currentNodePtr->data;
	}
	else
	{
		return 0;
	}
}

template <typename NODETYPE>
void List<NODETYPE>::sort()
{
	if (firstPtr != 0)
	{
		if (firstPtr->nextPtr == firstPtr)
		{
			return;
		}
		else
		{
			bool sorted = true;

			while (sorted)
			{
				sorted = false;
				ListNode<NODETYPE>* currentPtr = firstPtr;
				ListNode<NODETYPE>* secondCurrentPtr = currentPtr->nextPtr;

				for (; secondCurrentPtr->nextPtr != firstPtr; currentPtr = currentPtr->nextPtr, secondCurrentPtr = secondCurrentPtr->nextPtr)
				{
					if (currentPtr->data > secondCurrentPtr->data)
					{
						ListNode<NODETYPE>* prevCurrentPtr = currentPtr->prevPtr;
						ListNode<NODETYPE>* nextSecondCurrentPtr = secondCurrentPtr->nextPtr;

						prevCurrentPtr->nextPtr = secondCurrentPtr;
						secondCurrentPtr->prevPtr = prevCurrentPtr;
						secondCurrentPtr->nextPtr = currentPtr;
						currentPtr->prevPtr = secondCurrentPtr;
						currentPtr->nextPtr = nextSecondCurrentPtr;
						nextSecondCurrentPtr->prevPtr = currentPtr;

						if (currentPtr == firstPtr)
						{
							firstPtr->prevPtr = secondCurrentPtr;
							firstPtr->nextPtr = nextSecondCurrentPtr;
							firstPtr = secondCurrentPtr;
						}

						currentPtr = currentPtr->prevPtr;
						secondCurrentPtr = secondCurrentPtr->nextPtr;
						sorted = true;
					}
				}
				if (currentPtr->data > secondCurrentPtr->data)
				{
					ListNode<NODETYPE>* prevCurrentPtr = currentPtr->prevPtr;
					ListNode<NODETYPE>* nextSecondCurrentPtr = secondCurrentPtr->nextPtr;

					prevCurrentPtr->nextPtr = secondCurrentPtr;
					secondCurrentPtr->prevPtr = prevCurrentPtr;
					secondCurrentPtr->nextPtr = currentPtr;
					currentPtr->prevPtr = secondCurrentPtr;
					currentPtr->nextPtr = nextSecondCurrentPtr;
					nextSecondCurrentPtr->prevPtr = currentPtr;

					if (currentPtr == firstPtr)
					{
						firstPtr->prevPtr = secondCurrentPtr;
						firstPtr->nextPtr = nextSecondCurrentPtr;
						firstPtr = secondCurrentPtr;
					}

					currentPtr = currentPtr->prevPtr;
					secondCurrentPtr = secondCurrentPtr->nextPtr;
					sorted = true;
				}
			}
		}
	}
}