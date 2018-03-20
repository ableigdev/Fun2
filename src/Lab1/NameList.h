#pragma once

#include "List.h"
#include <string>

template <typename NODETYPE>
class NameList : public List<NODETYPE>
{
public:
	explicit NameList(const std::string& = "");
	explicit NameList(const NameList<NODETYPE>&);
	virtual ~NameList();

	void setNameClassList(const std::string&);
	std::string getNameClassList() const;

private:
	std::string m_NameList;
};


template <typename NODETYPE>
NameList<NODETYPE>::NameList(const std::string& str)
	: List(),
	m_NameList(str)
{

}

template <typename NODETYPE>
NameList<NODETYPE>::NameList(const NameList<NODETYPE>& right)
	: m_NameList(right.m_NameList)
{

}

template <typename NODETYPE>
NameList<NODETYPE>::~NameList()
{
	m_NameList.clear();
}

template <typename NODETYPE>
void NameList<NODETYPE>::setNameClassList(const std::string& str)
{
	m_NameList = str;
}

template <typename NODETYPE>
std::string NameList<NODETYPE>::getNameClassList() const
{
	return m_NameList;
}