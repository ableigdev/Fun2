#include <iostream>
#include <cstdlib>
#include <ctime>
#include "List.h"
#include "ListIterator.h"
#include "Student.h"
#include "NameList.h"


int main()
{
	std::srand(time(0));
	List<int> lists;

	for (int i = 0; i < 10; ++i)
	{
		lists.pushFront(rand() % 100);
	}


	lists.sort();
	lists.print();
	int* value = &lists.getReferencesCurrentData();

	*value = 30;

	lists.sortCurrentNodePtr();

	lists.print();

	std::cin.get();

	return 0;
}