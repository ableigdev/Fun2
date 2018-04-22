#include <iostream>
#include <cstdlib>
#include <ctime>
#include "List.h"
#include "ListIterator.h"
#include "Student.h"
#include "NameList.h"
#include "blist.h"

#ifdef UNICODE
#define out std::wcout
#define typeString wchar_t
#else
#define out std::cout
#define typeString char
#endif // UNICODE


int main()
{
	std::srand(time(0));
	
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

	std::cin.get();
	system("pause");

	return 0;
}