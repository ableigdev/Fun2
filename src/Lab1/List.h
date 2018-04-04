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

	inline bool isEmpty() const;
	inline size_t getSize() const;

	void sort();
	void sortCurrentNodePtr();

	inline bool operator!() const;
	const List<NODETYPE>& operator=(const List<NODETYPE>&);
	List<NODETYPE>& operator++();
	List<NODETYPE>& operator--();

	NODETYPE& getReferencesCurrentData() const;
	NODETYPE getValueCurrentData() const;

	template <typename NODETYPE>
	friend std::ostream& operator<<(std::ostream&, const List<NODETYPE>&);

private:
	template <typename NODETYPE>
	struct ListNode
	{
		NODETYPE data; 
		ListNode<NODETYPE>* nextPtr;
		ListNode<NODETYPE>* prevPtr;
	};
						
	ListNode<NODETYPE>* firstPtr;
	ListNode<NODETYPE>* currentNodePtr;
	size_t m_Size;

private:
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
	: firstPtr(0),
	currentNodePtr(0),
	m_Size(0)
{
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
	if (!*this && !rList && this != &rList)
	{
		ListNode<NODETYPE>* currentFirstPtr = firstPtr;
		ListNode<NODETYPE>* currentRightPtr = rList.firstPtr;
				
		do 
		{
			currentFirstPtr->data = currentRightPtr->data;
			currentFirstPtr = currentFirstPtr->nextPtr;
			currentRightPtr = currentRightPtr->nextPtr;
		} while (currentRightPtr != rList.firstPtr && currentFirstPtr != firstPtr);

		if (m_Size > rList.m_Size)
		{
			currentFirstPtr->prevPtr->nextPtr = firstPtr;
			firstPtr->prevPtr = currentFirstPtr->prevPtr;
			ListNode<NODETYPE>* tempPtr = 0;

			do
			{
				tempPtr = currentFirstPtr;
				currentFirstPtr = currentFirstPtr->nextPtr;
				delete tempPtr;
				--m_Size;
			} while (currentFirstPtr != firstPtr);	
		}
		

		if (m_Size < rList.m_Size)
		{
			do
			{
				pushBack(currentRightPtr->data);
				currentRightPtr = currentRightPtr->nextPtr;
			} while (currentRightPtr != rList.firstPtr);
		}
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
	if (currentNodePtr != 0)	
		currentNodePtr = currentNodePtr->nextPtr;

	return *this;
}

template <typename NODETYPE>
List<NODETYPE>& List<NODETYPE>::operator--()
{
	if (currentNodePtr != 0)	
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
	if (firstPtr == 0)
	{
		currentNodePtr = 0;
	}
	currentNodePtr = firstPtr->prevPtr;
}

template <typename NODETYPE>
void List<NODETYPE>::pushFront(const NODETYPE& value)
{
	ListNode<NODETYPE>* newPtr = getNewNode(value);

	if (!isEmpty())
	{	
		firstPtr->prevPtr->nextPtr = newPtr;
		newPtr->prevPtr = firstPtr->prevPtr;
	}
	else
	{
		currentNodePtr = firstPtr = newPtr;
	}
	newPtr->nextPtr = firstPtr;
	firstPtr->prevPtr = newPtr;
	firstPtr = newPtr;
	
	++m_Size;
}

template <typename NODETYPE>
void List<NODETYPE>::pushBack(const NODETYPE& value)
{
	ListNode<NODETYPE>* newPtr = getNewNode(value);

	if (isEmpty())
	{
		currentNodePtr = firstPtr->nextPtr = firstPtr->prevPtr = firstPtr = newPtr;
	}
	else
	{
		ListNode<NODETYPE>* tempPtr = firstPtr->prevPtr;
		newPtr->nextPtr = firstPtr;
		newPtr->prevPtr = firstPtr->prevPtr;
		firstPtr->prevPtr = newPtr;
		tempPtr->nextPtr = newPtr;
	}
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

		do
		{
			if (currentPtr->data == value)
			{
				ListNode<NODETYPE>* prevTempPtr = currentPtr->prevPtr;
				ListNode<NODETYPE>* nextTempPtr = currentPtr->nextPtr;

				prevTempPtr->nextPtr = nextTempPtr;
				nextTempPtr->prevPtr = prevTempPtr;

				if (currentPtr == firstPtr)
				{
					firstPtr = nextTempPtr != firstPtr ? nextTempPtr : 0;
				}
				
				delete currentPtr;
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
		} while (currentPtr != firstPtr);

		m_Size = 0;
		firstPtr = 0;
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
NODETYPE& List<NODETYPE>::getReferencesCurrentData() const
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
	currentNodePtr = currentPtr;
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
void List<NODETYPE>::sortCurrentNodePtr()
{
	if (!isEmpty())
	{
		if (currentNodePtr->data > currentNodePtr->nextPtr->data)
		{
			ListNode<NODETYPE>* tempPtr = currentNodePtr->nextPtr;

			while (currentNodePtr->data > tempPtr->data)
			{
				tempPtr = tempPtr->nextPtr;
			}

			currentNodePtr->prevPtr->nextPtr = currentNodePtr->nextPtr;
			currentNodePtr->nextPtr->prevPtr = currentNodePtr->prevPtr;
				
			tempPtr->prevPtr->nextPtr = currentNodePtr;
			currentNodePtr->prevPtr = tempPtr->prevPtr;
			currentNodePtr->nextPtr = tempPtr;
			tempPtr->prevPtr = currentNodePtr;
		}

		if (currentNodePtr->data < currentNodePtr->prevPtr->data)
		{
			if (currentNodePtr == firstPtr)
			{
				return;
			}

			if (currentNodePtr->data < firstPtr->data)
			{
				currentNodePtr->prevPtr->nextPtr = currentNodePtr->nextPtr;
				currentNodePtr->nextPtr->prevPtr = currentNodePtr->prevPtr;

				firstPtr->prevPtr->nextPtr = currentNodePtr;
				currentNodePtr->prevPtr = firstPtr->prevPtr;
				currentNodePtr->nextPtr = firstPtr;
				firstPtr->prevPtr = currentNodePtr;
				firstPtr = currentNodePtr;
			}
			else
			{
				ListNode<NODETYPE>* tempPtr = currentNodePtr->prevPtr;

				while (currentNodePtr->data < tempPtr->data && tempPtr != firstPtr)
				{
					tempPtr = tempPtr->prevPtr;
				}

				currentNodePtr->prevPtr->nextPtr = currentNodePtr->nextPtr;
				currentNodePtr->nextPtr->prevPtr = currentNodePtr->prevPtr;

				tempPtr->nextPtr->prevPtr = currentNodePtr;
				currentNodePtr->nextPtr = tempPtr->nextPtr;
				currentNodePtr->prevPtr = tempPtr;
				tempPtr->nextPtr = currentNodePtr;
			}
		}
	}
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
