#include <iostream>
#include <cstdlib>
#include <ctime>
#include "List.h"
#include "ListIterator.h"
#include "Student.h"
#include "NameList.h"


int main()
{
	NameList<int> list("first");


	for (int i = 0; i < 10; ++i)
	{
		list.pushFront(i);
	}

	std::cout << list << std::endl;

	list.sort();

	std::cout << list << std::endl;

	std::cout << "name: " << list.getNameClassList() << std::endl;
	

	NameList<int> list2;

	list2.pushInSortList(3);
	list2.pushInSortList(1);
	list2.pushInSortList(8);
	list2.pushInSortList(5);
	list2.pushInSortList(2);
	list2.pushInSortList(3);
	list2.pushInSortList(4);

	std::cout << list2 << std::endl;

	list2.setNameClassList("second");

	std::cout << "name: " << list2.getNameClassList() << std::endl;

	NameList<int> list3(list2);

	std::cout << "list3: " << list3 << std::endl;

	NameList<int> list4;

	list4 = list3;

	std::cout << "list4: " << list4 << std::endl;

	std::cin.get();

	return 0;
}