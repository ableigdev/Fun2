#pragma once


template <class NODETYPE>
class List
{
public:
	List(); 
	List(const List<NODETYPE>&);
	~List();

	void pushFront(const NODETYPE&);
	void pushBack(const NODETYPE&);
	void pushInSortList(const NODETYPE&);

	bool deleteElement(NODETYPE);
	bool deleteAllElements();

	bool findValue(const NODETYPE&);

	bool isEmpty() const;
	void print() const;

	bool operator!() const;
	const List<NODETYPE>& operator=(const List<NODETYPE>&);

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
	void copyList(const ListNode<NODETYPE>*);
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
	if (!rList)
	{
		copyList(rList.firstPtr);
	}
	else
	{
		firstPtr = 0;
		currentNodePtr = 0;
	}
	
}

template <typename NODETYPE>
List<NODETYPE>::~List()
{
	if (!isEmpty())
	{
		deleteAllElements();
	}
}

template <typename NODETYPE>
const List<NODETYPE>& List<NODETYPE>::operator=(const List<NODETYPE>& rList)
{
	if (this != &rList)
	{
		deleteAllElements();
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
bool List<NODETYPE>::isEmpty() const
{
	return firstPtr == 0;
}

template <typename NODETYPE>
void List<NODETYPE>::copyList(const ListNode<NODETYPE>* rightPtr)
{
	const ListNode<NODETYPE>* currentRightPtr = rightPtr;
	
	while (currentRightPtr->nextPtr != rightPtr)
	{
		pushBack(currentRightPtr->data);
		currentRightPtr = currentRightPtr->nextPtr;
	}
	pushBack(currentRightPtr->data);
}
template <typename NODETYPE>
void List<NODETYPE>::print() const
{
	if (!isEmpty())
	{
		ListNode<NODETYPE>* currentPtr = firstPtr;

		while (currentPtr->nextPtr != firstPtr)
		{
			std::cout << currentPtr->data << ' ';
			currentPtr = currentPtr->nextPtr;
		}
		std::cout << currentPtr->data;
	}
	std::cout << std::endl;
}

template <typename NODETYPE>
void List<NODETYPE>::pushFront(const NODETYPE& value)
{
	ListNode<NODETYPE> *newPtr = new ListNode<NODETYPE>;
	newPtr->data = value;
	newPtr->nextPtr = 0;
	newPtr->prevPtr = 0;

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
	newPtr->nextPtr = 0;
	newPtr->prevPtr = 0;

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
	if (isEmpty())
	{
		pushFront(value);
	}
	else
	{
		if (value <= firstPtr->data)
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
			newPtr->nextPtr = 0;
			newPtr->prevPtr = 0;

			ListNode<NODETYPE>* currentPtr = firstPtr;

			while (currentPtr->nextPtr != firstPtr)
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
			}
			if (newPtr->data <= currentPtr->data)
			{
				ListNode<NODETYPE>* tempPtr = currentPtr->prevPtr;
				tempPtr->nextPtr = newPtr;
				newPtr->prevPtr = tempPtr;
				newPtr->nextPtr = currentPtr;
				currentPtr->prevPtr = newPtr;
			}
		}
	}
}

template <typename NODETYPE>
bool List<NODETYPE>::deleteElement(NODETYPE value)
{
	if (!isEmpty())
	{
		ListNode<NODETYPE>* currentPtr = firstPtr;
		ListNode<NODETYPE>* tempPtr = 0;

		if (currentPtr->data == value)
		{
			ListNode<NODETYPE>* prevTempPtr = currentPtr->prevPtr;
			ListNode<NODETYPE>* nextTempPtr = currentPtr->nextPtr;
			tempPtr = currentPtr;

			prevTempPtr->nextPtr = nextTempPtr;
			nextTempPtr->prevPtr = prevTempPtr;

			firstPtr = nextTempPtr;

			delete tempPtr;

			return true;
		}
		else
		{
			while (currentPtr->nextPtr != firstPtr)
			{
				if (currentPtr->data == value)
				{
					ListNode<NODETYPE>* prevTempPtr = currentPtr->prevPtr;
					ListNode<NODETYPE>* nextTempPtr = currentPtr->nextPtr;
					tempPtr = currentPtr;

					prevTempPtr->nextPtr = nextTempPtr;
					nextTempPtr->prevPtr = prevTempPtr;

					delete tempPtr;

					return true;
				}
				currentPtr = currentPtr->nextPtr;
			}

			if (currentPtr->data == value)
			{
				ListNode<NODETYPE>* prevTempPtr = currentPtr->prevPtr;
				ListNode<NODETYPE>* nextTempPtr = currentPtr->nextPtr;
				tempPtr = currentPtr;

				prevTempPtr->nextPtr = nextTempPtr;
				nextTempPtr->prevPtr = prevTempPtr;

				delete tempPtr;

				return true;
			}
			return false;
		}
		
	}
	else
	{
		return false;
	}
}

template <typename NODETYPE>
bool List<NODETYPE>::deleteAllElements()
{
	if (!isEmpty())
	{
		ListNode<NODETYPE>* currentPtr = firstPtr;
		ListNode<NODETYPE>* tempPtr;

		while (currentPtr->nextPtr != firstPtr)
		{
			tempPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
			delete tempPtr;
		}

		if (currentPtr != 0)
			delete currentPtr;

		return true;
	}
	else
	{
		return false;
	}
}

template <typename NODETYPE>
bool List<NODETYPE>::findValue(const NODETYPE& value)
{
	if (!isEmpty())
	{
		ListNode<NODETYPE>* currentPtr = firstPtr;

		if (currentPtr->data == value)
		{
			return true;
		}
		else
		{
			while (currentPtr->nextPtr != firstPtr)
			{
				if (currentPtr->data == value)
				{
					return true;
				}
				currentPtr = currentPtr->nextPtr;
			}
			if (currentPtr->data == value)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
}