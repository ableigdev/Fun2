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
	void setCurrentNodeOnTheEnd();

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
	size_t m_Size;

private:
	void copyList(ListNode<NODETYPE>*);
	void deleteRemaindList(ListNode<NODETYPE>*);
	ListNode<NODETYPE>* getNewNode(const NODETYPE&);
	ListNode<NODETYPE>* fusion(ListNode<NODETYPE>*, NODETYPE, ListNode<NODETYPE>*, NODETYPE);
	ListNode<NODETYPE>* merge_sort(ListNode<NODETYPE>*, NODETYPE);
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
	m_Size = rList.m_Size;

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
	merge_sort(firstPtr, m_Size);
}

template <typename NODETYPE>
typename List<NODETYPE>::ListNode<NODETYPE>* List<NODETYPE>::fusion(ListNode<NODETYPE>* p, NODETYPE P, ListNode<NODETYPE>* q, NODETYPE Q)
{
	ListNode<NODETYPE>* s;
	ListNode<NODETYPE>* e;

	s = NULL;
	while (P > 0 && Q > 0) {
		if (p->data <= q->data) 
		{
			/* select element from p list */
			e = p;
			p = p->nextPtr;
			P--;
		}
		else 
		{
			/* select element from q list */
			e = q;
			q = q->nextPtr;
			Q--;
		}
		/* detach e */
		e->prevPtr->nextPtr = e->nextPtr;
		e->nextPtr->prevPtr = e->prevPtr;
		e->nextPtr = e->prevPtr = e;
		if (s == NULL) 
		{
			s = e;
		}
		else 
		{
			/* insert e after s */
			e->prevPtr = s->prevPtr;
			e->nextPtr = s;
			s->prevPtr->nextPtr = e;
			s->prevPtr = e;
		}
	}
	if (P > 0) 
	{
		/* insert p at the end of s */
		if (s == NULL) {
			s = p;
		}
		else 
		{
			/* insert p after s */
			e = p->prevPtr; /* end element of p */
			p->prevPtr = s->prevPtr;
			e->nextPtr = s;
			s->prevPtr->nextPtr = p;
			s->prevPtr = e;
		}
	}
	if (Q > 0) 
	{
		/* insert q at the end of s */
		if (s == NULL) 
		{
			s = q;
		}
		else 
		{
			/* insert q after s */
			e = q->prevPtr; /* end element of p */
			q->prevPtr = s->prevPtr;
			e->nextPtr = s;
			s->prevPtr->nextPtr = q;
			s->prevPtr = e;
		}
	}
	return s;
}

template <typename NODETYPE>
typename List<NODETYPE>::ListNode<NODETYPE>* List<NODETYPE>::merge_sort(ListNode<NODETYPE>* s, NODETYPE S)
{
	ListNode<NODETYPE>* p;
	ListNode<NODETYPE>* q;

	int P;
	int Q;

	if (S < 2)
	{
		return s;
	}

	/* split p in 2 halves: p[0..P] and q[0..Q] */
	for (q = p = s, P = 0, Q = S; P < Q; P++, Q--) 
	{
		q = q->nextPtr;
	}

	p = merge_sort(p, P);
	q = merge_sort(q, Q);
	s = fusion(p, P, q, Q);
	return s;
}