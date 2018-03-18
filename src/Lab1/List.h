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

private:
	void copyList(ListNode<NODETYPE>*);
	void deleteRemaindList(ListNode<NODETYPE>*);
	ListNode<NODETYPE>* getNewNode(const NODETYPE&);
	void mergeSort(ListNode<NODETYPE>**);
	void findMid(ListNode<NODETYPE>*, ListNode<NODETYPE>**, ListNode<NODETYPE>**);
	static ListNode<NODETYPE>* mergeList(ListNode<NODETYPE>*, ListNode<NODETYPE>*);
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
	mergeSort(&firstPtr);
}

template <typename NODETYPE>
void List<NODETYPE>::mergeSort(ListNode<NODETYPE>** root)
{
	ListNode<NODETYPE>* list1;
	ListNode<NODETYPE>* list2;
	ListNode<NODETYPE>* head = *root;

	if ((head == 0) || (head->nextPtr == 0))
	{
		return;
	}


	findMid(head, &list1, &list2);

	mergeSort(&list1);
	mergeSort(&list2);

	*root = mergeList(list1, list2);
}

template <typename NODETYPE>
void List<NODETYPE>::findMid(ListNode<NODETYPE>* root, ListNode<NODETYPE>** list1, ListNode<NODETYPE>** list2)
{

	ListNode<NODETYPE>* slow;
	ListNode<NODETYPE>* fast;

	if ((root == 0) || (root->nextPtr == 0))
	{
		*list1 = root;
		*list2 = 0;
		return;
	}
	else
	{

		slow = root;
		fast = root->nextPtr;
		while (fast != firstPtr)
		{
			fast = fast->nextPtr;
			if (fast != firstPtr)
			{
				slow = slow->nextPtr;
				fast = fast->nextPtr;
			}
		} 


		*list1 = root;
		*list2 = slow->nextPtr;
		slow->nextPtr = 0;

	}

}

template <typename NODETYPE>
typename List<NODETYPE>::ListNode<NODETYPE>* List<NODETYPE>::mergeList(ListNode<NODETYPE>* list1, ListNode<NODETYPE>* list2)
{
	ListNode<NODETYPE> dummy_head;
	dummy_head.data = 0;
	dummy_head.nextPtr = 0;
	dummy_head.prevPtr = 0;
	
	List<NODETYPE>::ListNode<NODETYPE>* tail = &dummy_head;

	while ((list1 != 0) && (list2 != 0))
	{
		ListNode<NODETYPE>** min = (list1->data < list2->data) ? &list1 : &list2;
		ListNode<NODETYPE>* next = (*min)->nextPtr;
		tail = tail->nextPtr = *min;
		*min = next;
	}
	tail->nextPtr = list1 ? list1 : list2;
	return dummy_head.nextPtr;
}