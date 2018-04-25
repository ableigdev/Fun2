#include <iostream>
#include <cstdlib>
#include <ctime>
#include "List.h"
#include "ListIterator.h"
#include "Student.h"
#include "NameList.h"
#include "blist.h"


int main()
{
	std::srand(time(0));
	{
		List<int> list;

		for (int i = 0; i < 5; ++i)
		{
			list.pushBack(i);
		}

		for (int i = 0; i < 5; ++i)
		{
			list.pushBack(rand() % 3000000);
		}

		time_t start = clock();
		list.sort();
		time_t finish = clock();

		if (list.bubbleSort())
		{
			std::cout << "good" << std::endl;
		}
		else
		{
			std::cout << "bad" << std::endl;
		}

		out << list << std::endl;

		std::cout << "time: " << finish - start << std::endl;
		out << "Counter compare: " << list.getCounterCompare() << std::endl;
		out << "Counter recursive call: " << list.getCounterRecursiveCall() << std::endl;
	}
	
	{
	TBList<int> list;

	for (int i = 0; i < 1000000; ++i)
	{
	list.AddBeforeHead(rand() % 3000000);
	}

	time_t start = clock();
	list.SortListBiDir();
	time_t finish = clock();

	out << "time: " << finish - start << std::endl;
	out << "Counter compare: " << list.getCounterCompare() << std::endl;
	out << "Counter recursive call: " << list.getCounterRecursiveCall() << std::endl;
	}
	{

	List<int> lists;

	for (int i = 0; i < 1000000; ++i)
	{
	lists.pushFront(rand() % 3000000);
	}

	time_t start = clock();
	lists.sort();
	time_t finish = clock();

	out << "time: " << finish - start << std::endl;

	if (lists.bubbleSort())
	{
	out << "Sort good" << std::endl;
	}
	else
	{
	out << "Sort bad" << std::endl;
	}

	out << "Counter compare: " << lists.getCounterCompare() << std::endl;
	out << "Counter recursive call: " << lists.getCounterRecursiveCall() << std::endl;
	}
	
	system("pause");

	return 0;
}