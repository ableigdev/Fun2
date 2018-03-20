#pragma once

#include "List.h"

template <typename NODETYPE>
class ListIterator
{
public:
	ListIterator(const List<NODETYPE>&);
	ListIterator(const ListIterator<NODETYPE>&);

	ListIterator<NODETYPE>& operator++();
	ListIterator<NODETYPE>& operator--();
	bool operator!();
	ListIterator<NODETYPE>& operator=(const ListIterator<NODETYPE>&);
	ListIterator<NODETYPE>& operator=(const List<NODETYPE>&);
	NODETYPE operator*();
private:
	List<NODETYPE> m_List;
	size_t m_Index;
};

template <typename NODETYPE>
ListIterator<NODETYPE>::ListIterator(const List<NODETYPE>& list)
	: m_List(list),
	  m_Index(0)
{
	m_List.setCurrentNodeOnTheBegin();
}

template <typename NODETYPE>
ListIterator<NODETYPE>::ListIterator(const ListIterator<NODETYPE>& iterator)
: m_List(iterator.m_List),
  m_Index(iterator.m_Index)
{
	
}

template <typename NODETYPE>
ListIterator<NODETYPE>& ListIterator<NODETYPE>::operator=(const ListIterator<NODETYPE>& right)
{
	*this = right;
} 

template <typename NODETYPE>
ListIterator<NODETYPE>& ListIterator<NODETYPE>::operator=(const List<NODETYPE>& right)
{
	m_List = right.m_List;
}

template <typename NODETYPE>
ListIterator<NODETYPE>& ListIterator<NODETYPE>::operator++()
{
	++m_List;
	++m_Index;
	
	return *this;
}

template <typename NODETYPE>
ListIterator<NODETYPE>& ListIterator<NODETYPE>::operator--()
{
	--m_List;
	--m_Index;

	return *this;
}

template <typename NODETYPE>
bool ListIterator<NODETYPE>::operator!()
{
	return m_Index < m_List.getSize();
}

template <typename NODETYPE>
NODETYPE ListIterator<NODETYPE>::operator*()
{
	return m_List.getValueCurrentData();
}

