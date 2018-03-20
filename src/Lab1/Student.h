#pragma once

#include <string>
#include <iostream>

template <typename TYPESTRING>
class Student
{
public:
	Student();
	Student(const Student<TYPESTRING>&);

	void setName(const std::basic_string<TYPESTRING>&);
	std::basic_string<TYPESTRING> getName() const;

	void setSurname(const std::basic_string<TYPESTRING>&);
	std::basic_string<TYPESTRING> getSurname() const;

	void setLastname(const std::basic_string<TYPESTRING>&);
	std::basic_string<TYPESTRING> getLastname() const;

	void setBirthYear(int);
	short int getBirthYear() const;

	void setAverageGrade(float);
	float getAverageGrade() const;

	const Student<TYPESTRING>& operator=(const Student<TYPESTRING>&);
	bool operator==(const Student<TYPESTRING>&) const;
	bool operator!=(const Student<TYPESTRING>&) const;
	bool operator>=(const Student<TYPESTRING>&) const;
	bool operator<=(const Student<TYPESTRING>&) const;
	bool operator>(const Student<TYPESTRING>&) const;
	bool operator<(const Student<TYPESTRING>&) const;

	template <typename TYPESTRING>
	friend std::ostream& operator<<(std::ostream&, const Student<TYPESTRING>&);
	template <typename TYPESTRING>
	friend std::istream& operator>>(std::istream&, Student<TYPESTRING>&);

	template <typename TYPESTRING>
	friend std::wostream& operator<<(std::wostream&, const Student<TYPESTRING>&);
	template <typename TYPESTRING>
	friend std::wistream& operator >> (std::wistream&, Student<TYPESTRING>&);

private:
	int compareStudents(const Student<TYPESTRING>&) const;

private:
	std::basic_string<TYPESTRING> m_Name {};
	std::basic_string<TYPESTRING> m_Surname {};
	std::basic_string<TYPESTRING> m_Lastname {};
	short int m_BirthYear;
	float m_AverageGrade;
};



template <typename TYPESTRING>
Student<TYPESTRING>::Student()
	: m_BirthYear(0),
	m_AverageGrade(0.0)
{

}

template <typename TYPESTRING>
Student<TYPESTRING>::Student(const Student<TYPESTRING>& someStudent)
	: m_Name(someStudent.m_Name),
	m_Surname(someStudent.m_Surname),
	m_Lastname(someStudent.m_Lastname),
	m_BirthYear(someStudent.m_BirthYear),
	m_AverageGrade(someStudent.m_AverageGrade)
{

}

template <typename TYPESTRING>
void Student<TYPESTRING>::setName(const std::basic_string<TYPESTRING>& name)
{
	m_Name = name;
}

template <typename TYPESTRING>
std::basic_string<TYPESTRING> Student<TYPESTRING>::getName() const
{
	return m_Name;
}

template <typename TYPESTRING>
void Student<TYPESTRING>::setSurname(const std::basic_string<TYPESTRING>& surname)
{
	m_Surname = surname;
}

template <typename TYPESTRING>
std::basic_string<TYPESTRING> Student<TYPESTRING>::getSurname() const
{
	return m_Surname;
}

template <typename TYPESTRING>
void Student<TYPESTRING>::setLastname(const std::basic_string<TYPESTRING>& lastname)
{
	m_Lastname = lastname;
}

template <typename TYPESTRING>
std::basic_string<TYPESTRING> Student<TYPESTRING>::getLastname() const
{
	return m_Lastname;
}

template <typename TYPESTRING>
void Student<TYPESTRING>::setBirthYear(int year)
{
	m_BirthYear = year;
}

template <typename TYPESTRING>
short int Student<TYPESTRING>::getBirthYear() const
{
	return m_BirthYear;
}

template <typename TYPESTRING>
void Student<TYPESTRING>::setAverageGrade(float averageGrade)
{
	m_AverageGrade = averageGrade;
}

template <typename TYPESTRING>
float Student<TYPESTRING>::getAverageGrade() const
{
	return m_AverageGrade;
}

template <typename TYPESTRING>
const Student<TYPESTRING>& Student<TYPESTRING>::operator=(const Student& right)
{
	if (this != &right)
	{
		m_Name = right.m_Name;
		m_Surname = right.m_Surname;
		m_Lastname = right.m_Lastname;
		m_BirthYear = right.m_BirthYear;
		m_AverageGrade = right.m_AverageGrade;
	}

	return *this;
}

template <typename TYPESTRING>
int Student<TYPESTRING>::compareStudents(const Student<TYPESTRING>& right) const
{
	int result = m_Surname.compare(right.m_Surname);

	if (result == 0)
	{
		result = m_Name.compare(right.m_Name);

		if (result == 0)
		{
			result = m_Lastname.compare(right.m_Lastname);

			if (result == 0)
			{
				return result;
			}
		}
	}

	return result;
}

template <typename TYPESTRING>
bool Student<TYPESTRING>::operator==(const Student<TYPESTRING>& right) const
{
	return compareStudents(right) == 0;
}

template <typename TYPESTRING>
bool Student<TYPESTRING>::operator!=(const Student<TYPESTRING>& right) const
{
	return !(*this == right);
}

template <typename TYPESTRING>
bool Student<TYPESTRING>::operator>=(const Student<TYPESTRING>& right) const
{
	return compareStudents(right) != -1;
}

template <typename TYPESTRING>
bool Student<TYPESTRING>::operator<=(const Student<TYPESTRING>& right) const
{
	return compareStudents(right) != 1;
}

template <typename TYPESTRING>
bool Student<TYPESTRING>::operator>(const Student<TYPESTRING>& right) const
{
	return compareStudents(right) == 1;
}

template <typename TYPESTRING>
bool Student<TYPESTRING>::operator<(const Student<TYPESTRING>& right) const
{
	return compareStudents(right) == -1;
}

template <typename TYPESTRING>
std::ostream& operator<<(std::ostream& output, const Student<TYPESTRING>& right)
{
	output << right.m_Surname << " " << right.m_Name << " "
		<< right.m_Lastname << " " << right.m_BirthYear << " "
		<< right.m_AverageGrade << std::endl;

	return output;
}

template <typename TYPESTRING>
std::istream& operator >> (std::istream& input, Student<TYPESTRING>& right)
{
	input >> right.m_Surname >> right.m_Name >> right.m_Lastname
		>> right.m_BirthYear >> right.m_AverageGrade;

	return input;
}

template <typename TYPESTRING>
std::wostream& operator<<(std::wostream& output, const Student<TYPESTRING>& right)
{
	output << right.m_Surname << " " << right.m_Name << " "
		<< right.m_Lastname << " " << right.m_BirthYear << " "
		<< right.m_AverageGrade << std::endl;

	return output;
}

template <typename TYPESTRING>
std::wistream& operator >> (std::wistream& input, Student<TYPESTRING>& right)
{
	input >> right.m_Surname >> right.m_Name >> right.m_Lastname
		>> right.m_BirthYear >> right.m_AverageGrade;

	return input;
}

