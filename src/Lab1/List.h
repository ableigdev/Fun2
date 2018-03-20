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
	virtual ~List();

	void pushFront(const NODETYPE&);
	void pushBack(const NODETYPE&);
	void pushInSortList(const NODETYPE&);

	void setCurrentNodeOnTheBegin();
	void setCurrentNodeOnTheEnd();

	bool deleteElement(NODETYPE);
	void deleteAllElements();

	bool findValue(const NODETYPE&);

	bool isEmpty() const;
	size_t getSize() const;
	void print() const;

	void sort();

	bool operator!() const;
	const List<NODETYPE>& operator=(const List<NODETYPE>&);
	List<NODETYPE>& operator++();
	List<NODETYPE>& operator--();

	const NODETYPE& getReferencesCurrentData() const;
	NODETYPE getValueCurrentData() const;

	template <typename NODETYPE>
	friend std::ostream& operator<<(std::ostream&, const List<NODETYPE>&);

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
	size_t m_Size;

private:
	void copyList(ListNode<NODETYPE>*);
	void deleteRemaindList(ListNode<NODETYPE>*);
	ListNode<NODETYPE>* getNewNode(const NODETYPE&);
	ListNode<NODETYPE>* fusion(ListNode<NODETYPE>*, size_t, ListNode<NODETYPE>*, size_t);
	ListNode<NODETYPE>* mergeSort(ListNode<NODETYPE>*, size_t);
};

template <typename NODETYPE>
List<NODETYPE>::List()
	: firstPtr(0),
	currentNodePtr(0),
	m_Size(0)
{
	
}

template <typename NODETYPE>
List<NODETYPE>::List(const List<NODETYPE>& rList)
{
	firstPtr = 0;
	currentNodePtr = 0;
	m_Size = 0;

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

	return *this;
}

template <typename NODETYPE>
List<NODETYPE>& List<NODETYPE>::operator--()
{
	if (currentNodePtr == 0)
		throw ReadAccessViolation();
	
	currentNodePtr = currentNodePtr->prevPtr;

	return *this;
}

template <typename NODETYPE>
typename List<NODETYPE>::ListNode<NODETYPE>* List<NODETYPE>::getNewNode(const NODETYPE& value)
{
	ListNode<NODETYPE> *newPtr = new ListNode<NODETYPE>;
	newPtr->data = value;

	return newPtr;
}

template <typename NODETYPE>
bool List<NODETYPE>::isEmpty() const
{
	return firstPtr == 0;
}

template <typename NODETYPE>
size_t List<NODETYPE>::getSize() const
{
	return m_Size;
}

template <typename NODETYPE>
void List<NODETYPE>::setCurrentNodeOnTheBegin()
{
	currentNodePtr = firstPtr;
}

template <typename NODETYPE>
void List<NODETYPE>::setCurrentNodeOnTheEnd()
{
	currentNodePtr = firstPtr->prevPtr;
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
	ListNode<NODETYPE>* newPtr = getNewNode(value);

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
	++m_Size;
}

template <typename NODETYPE>
void List<NODETYPE>::pushBack(const NODETYPE& value)
{
	ListNode<NODETYPE>* newPtr = getNewNode(value);

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
	++m_Size;
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
		ListNode<NODETYPE>* newPtr = getNewNode(value);
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
				++m_Size;
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
				--m_Size;
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
			--m_Size;
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
	if (currentNodePtr == 0)
		throw ReadAccessViolation();

	return currentNodePtr->data;
}

template <typename NODETYPE>
NODETYPE List<NODETYPE>::getValueCurrentData() const
{
	if (currentNodePtr == 0)
		throw ReadAccessViolation();
	
	return currentNodePtr->data;
}

template <typename NODETYPE>
void List<NODETYPE>::sort()
{
	mergeSort(firstPtr, m_Size);
}

template <typename NODETYPE>
typename List<NODETYPE>::ListNode<NODETYPE>* List<NODETYPE>::fusion(ListNode<NODETYPE>* leftListPtr, size_t leftListSize, ListNode<NODETYPE>* rightListPtr, size_t rightListSize)
{
	ListNode<NODETYPE>* currentPtr = 0;
	ListNode<NODETYPE>* tempPtr;

	while (leftListSize > 0 && rightListSize > 0)
	{
		if (leftListPtr->data <= rightListPtr->data)
		{
			/* select element from leftListPtr list */
			tempPtr = leftListPtr;
			leftListPtr = leftListPtr->nextPtr;
			--leftListSize;
		}
		else 
		{
			/* select element from rightListPtr list */
			tempPtr = rightListPtr;
			rightListPtr = rightListPtr->nextPtr;
			--rightListSize;
		}
		/* detach tempPtr */
		tempPtr->prevPtr->nextPtr = tempPtr->nextPtr;
		tempPtr->nextPtr->prevPtr = tempPtr->prevPtr;
		tempPtr->nextPtr = tempPtr->prevPtr = tempPtr;
		
		if (currentPtr == 0)
		{
			currentPtr = tempPtr;
		}
		else 
		{
			/* insert tempPtr after currentPtr */
			tempPtr->prevPtr = currentPtr->prevPtr;
			tempPtr->nextPtr = currentPtr;
			currentPtr->prevPtr->nextPtr = tempPtr;
			currentPtr->prevPtr = tempPtr;
		}
	}

	if (leftListSize > 0)
	{
		/* insert leftListPtr at the end of currentPtr */
		if (currentPtr == 0)
		{
			currentPtr = leftListPtr;
		}
		else 
		{
			/* insert leftListPtr after currentPtr */
			tempPtr = leftListPtr->prevPtr; /* end element of leftListPtr */
			leftListPtr->prevPtr = currentPtr->prevPtr;
			tempPtr->nextPtr = currentPtr;
			currentPtr->prevPtr->nextPtr = leftListPtr;
			currentPtr->prevPtr = tempPtr;
		}
	}

	if (rightListSize > 0)
	{
		/* insert rightListPtr at the end of currentPtr */
		if (currentPtr == 0)
		{
			currentPtr = rightListPtr;
		}
		else 
		{
			/* insert rightListPtr after currentPtr */
			tempPtr = rightListPtr->prevPtr; /* end element of leftListPtr */
			rightListPtr->prevPtr = currentPtr->prevPtr;
			tempPtr->nextPtr = currentPtr;
			currentPtr->prevPtr->nextPtr = rightListPtr;
			currentPtr->prevPtr = tempPtr;
		}
	}

	firstPtr = currentPtr;
	return currentPtr;
}

template <typename NODETYPE>
typename List<NODETYPE>::ListNode<NODETYPE>* List<NODETYPE>::mergeSort(ListNode<NODETYPE>* rootPtr, size_t sizeList)
{
	ListNode<NODETYPE>* leftListPtr;
	ListNode<NODETYPE>* rightListPtr;

	size_t leftListSize;
	size_t rightListSize;

	if (sizeList < 2)
	{
		return rootPtr;
	}

	/* split p in 2 halves: p[0..P] and q[0..Q] */
	for (rightListPtr = leftListPtr = rootPtr, leftListSize = 0, rightListSize = sizeList; leftListSize < rightListSize; ++leftListSize, --rightListSize)
	{
		rightListPtr = rightListPtr->nextPtr;
	}

	leftListPtr = mergeSort(leftListPtr, leftListSize);
	rightListPtr = mergeSort(rightListPtr, rightListSize);
	rootPtr = fusion(leftListPtr, leftListSize, rightListPtr, rightListSize);
	return rootPtr;
}


template <typename NODETYPE>
std::ostream& operator<<(std::ostream& output, const List<NODETYPE>& right)
{
	for (ListIterator<NODETYPE> it = right; !it; ++it)
	{
		output << *it << " ";
	}

	return output;
}
