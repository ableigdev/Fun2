#include "Student.h"

Student::Student()
	: m_BirthYear(0),
	m_AverageGrade(0.0)
{

}

Student::Student(const Student& someStudent)
	: m_Name(someStudent.m_Name),
	m_Surname(someStudent.m_Surname),
	m_Lastname(someStudent.m_Lastname),
	m_BirthYear(someStudent.m_BirthYear),
	m_AverageGrade(someStudent.m_AverageGrade)
{

}

Student::~Student()
{

}

void Student::setName(const std::string& name)
{
	m_Name = name;
}

std::string Student::getName() const
{
	return m_Name;
}

void Student::setSurname(const std::string& surname)
{
	m_Surname = surname;
}

std::string Student::getSurname() const
{
	return m_Surname;
}

void Student::setLastname(const std::string& lastname)
{
	m_Lastname = lastname;
}

std::string Student::getLastname() const
{
	return m_Lastname;
}

void Student::setBirthYear(int year)
{
	m_BirthYear = year;
}

int Student::getBirthYear() const
{
	return m_BirthYear;
}

void Student::setAverageGrade(double averageGrade)
{
	m_AverageGrade = averageGrade;
}

double Student::getAverageGrade() const
{
	return m_AverageGrade;
}

const Student& Student::operator=(const Student& right)
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

int Student::compareStudents(const Student& right) const
{
	if (m_Surname > right.m_Surname && m_Name > right.m_Name && m_Lastname > right.m_Lastname)
	{
		return -1;
	}

	if (m_Surname < right.m_Surname && m_Name < right.m_Name && m_Lastname < right.m_Lastname)
	{
		return 1;
	}
	return 0;
}

bool Student::operator==(const Student& right) const
{
	return compareStudents(right) == 0;
}

bool Student::operator!=(const Student& right) const
{
	return !(*this == right);
}

bool Student::operator>=(const Student& right) const
{
	int result = compareStudents(right);
	return  result == 0 || result == 1;
}

bool Student::operator<=(const Student& right) const
{
	int result = compareStudents(right);
	return  result == 0 || result == -1;
}

bool Student::operator>(const Student& right) const
{
	return compareStudents(right) == 1;
}

bool Student::operator<(const Student& right) const
{
	return compareStudents(right) == -1;
}

std::ostream& operator<<(std::ostream& output, const Student& right)
{
	output << right.m_Surname << " " << right.m_Name << " "
		<< right.m_Lastname << " " << right.m_BirthYear << " "
		<< right.m_AverageGrade << std::endl;

	return output;
}

std::istream& operator >> (std::istream& input, Student& right)
{
	input >> right.m_Surname >> right.m_Name >> right.m_Lastname
		>> right.m_BirthYear >> right.m_AverageGrade;

	return input;
}

