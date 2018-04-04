#pragma once

#include "List.h"
#include <string>

template <typename NODETYPE, typename TYPESTRING>
class NameList : public List<NODETYPE>
{
public:
	explicit NameList(const std::basic_string<TYPESTRING>& = "");
	explicit NameList(const NameList<NODETYPE, TYPESTRING>&);
	virtual ~NameList() = default;

	void setNameClassList(const std::basic_string<TYPESTRING>&);
	std::basic_string<TYPESTRING> getNameClassList() const;

	const NameList<NODETYPE, TYPESTRING>& operator=(const NameList<NODETYPE, TYPESTRING>&);
private:
	std::basic_string<TYPESTRING> m_NameList;
};


template <typename NODETYPE, typename TYPESTRING>
NameList<NODETYPE, TYPESTRING>::NameList(const std::basic_string<TYPESTRING>& str)
	: List(),
	m_NameList(str)
{

}

template <typename NODETYPE, typename TYPESTRING>
NameList<NODETYPE, TYPESTRING>::NameList(const NameList<NODETYPE, TYPESTRING>& right)
	: List(),
	m_NameList(right.m_NameList)
{
	*this = right;
}

template <typename NODETYPE, typename TYPESTRING>
void NameList<NODETYPE, TYPESTRING>::setNameClassList(const std::basic_string<TYPESTRING>& str)
{
	m_NameList = str;
}

template <typename NODETYPE, typename TYPESTRING>
std::basic_string<TYPESTRING> NameList<NODETYPE, TYPESTRING>::getNameClassList() const
{
	return m_NameList;
}

template <typename NODETYPE, typename TYPESTRING>
const NameList<NODETYPE, TYPESTRING>& NameList<NODETYPE, TYPESTRING>::operator=(const NameList<NODETYPE, TYPESTRING>& right)
{
	if (this != &right)
	{
		List<NODETYPE>::operator=(right);
		m_NameList = right.m_NameList;
	}
	return *this;
}