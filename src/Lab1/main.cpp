#include <iostream>
#include "List.h"
#include "ListIterator.h"

int main()
{
	{
		List<int> list1;

		for (int i = 0; i < 5; ++i)
			list1.pushFront(i);

		List<int> list2(list1);

		List<int> list3;
		list3.pushBack(3);
		List<int> list4(list3);

		std::cout << "list1 == list2 is " << (list1 == list2) << std::endl;
		std::cout << "list3 == list4 is " << (list3 == list4) << std::endl;

		list3.pushFront(9);

		std::cout << "list3 == list4 is " << (list3 == list4) << std::endl;

		list4.pushBack(5);

		std::cout << "list3 == list4 is " << (list3 == list4) << std::endl;

	}
	{
		List<int> list1;

		for (int i = 0; i < 5; ++i)
			list1.pushBack(i);

		list1.print();
	}
	std::cin.get();

	return 0;
}