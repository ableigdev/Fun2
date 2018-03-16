#pragma once

#include <string>
#include <iostream>

class Student
{
public:
	Student();
	Student(const Student&);
	~Student();

	void setName(const std::string&);
	std::string getName() const;

	void setSurname(const std::string&);
	std::string getSurname() const;

	void setLastname(const std::string&);
	std::string getLastname() const;

	void setBirthYear(int);
	short int getBirthYear() const;

	void setAverageGrade(double);
	float getAverageGrade() const;

	const Student& operator=(const Student&);
	bool operator==(const Student&) const;
	bool operator!=(const Student&) const;
	bool operator>=(const Student&) const;
	bool operator<=(const Student&) const;
	bool operator>(const Student&) const;
	bool operator<(const Student&) const;

	friend std::ostream& operator<<(std::ostream&, const Student&);
	friend std::istream& operator>>(std::istream&, Student&);

private:
	int compareStudents(const Student&) const;

private:
	std::string m_Name {};
	std::string m_Surname {};
	std::string m_Lastname {};
	short int m_BirthYear;
	float m_AverageGrade;
};