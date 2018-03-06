#pragma once

#include "List.h"

template <typename NODETYPE>
class ListIterator
{
public:
	ListIterator(const List<NODETYPE>&);

	void operator++();
	void operator--();
	bool operator()();
	NODETYPE operator*();
private:
	List<NODETYPE> m_List;
};

template <typename NODETYPE>
ListIterator<NODETYPE>::ListIterator(const List<NODETYPE>& list)
	: m_List(list)
{
	m_List.setCurrentNodeOnTheBegin();
}

template <typename NODETYPE>
void ListIterator<NODETYPE>::operator++()
{
	++m_List;
}

template <typename NODETYPE>
void ListIterator<NODETYPE>::operator--()
{
	--m_List;
}

template <typename NODETYPE>
bool ListIterator<NODETYPE>::operator()()
{
	return m_List.currentNodePtr->nextPtr != m_List.firstPtr;
}

template <typename NODETYPE>
NODETYPE ListIterator<NODETYPE>::operator*()
{
	return m_List.getValueCurrentData();
}

template <typename NODETYPE>
bool operator==(const List<NODETYPE>& leftList, const List<NODETYPE>& rightList)
{
	ListIterator<NODETYPE> iterLeft(leftList);
	ListIterator<NODETYPE> iterRight(rightList);

	for (; iterLeft(); ++iterLeft, ++iterRight)
	{
		if (*iterLeft != *iterRight)
		{
			break;
		}
	}
	return !iterLeft() && !iterRight();
}