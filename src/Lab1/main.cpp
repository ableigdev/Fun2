#include <iostream>
#include "List.h"

int main()
{
	{
		List<int> list1;

		for (int i = 0; i < 5; ++i)
			list1.pushFront(i);

		list1.print();
		list1.deleteElement(0);
		list1.print();
		
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