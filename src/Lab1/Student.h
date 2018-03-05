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
	int getBirthYear() const;

	void setAverageGrade(double);
	double getAverageGrade() const;

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
	int m_BirthYear;
	double m_AverageGrade;
};