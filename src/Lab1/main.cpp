#include <iostream>
#include "List.h"
#include "Student.h"

int main()
{
	{
		Student stud1;
		Student stud2;

		std::cout << "Enter data: ";
		std::cin >> stud1;
		std::cout << "Student: " << stud1;

		stud2 = stud1;

		Student stud3(stud2);

		if (stud1 == stud2)
			std::cout << "stud1 == stud2" << std::endl;

		if (stud1 == stud3)
			std::cout << "stud1 == stud3" << std::endl;

		if (stud2 == stud3)
			std::cout << "stud2 == stud3" << std::endl;

		if (stud2 >= stud3)
			std::cout << "stud2 >= stud3" << std::endl;

		if (stud2 <= stud3)
			std::cout << "stud2 <= stud3" << std::endl;


		stud2.setSurname("Aaaaaaa");
		stud2.setName("AAAaaa");
		stud2.setLastname("Aaaaaa");

		if (stud2 > stud1)
			std::cout << "stud2 > stud1" << std::endl;
		
		if (stud2 >= stud1)
			std::cout << "stud2 >= stud1" << std::endl;

		if (stud2 != stud1)
			std::cout << "stud2 != stud1" << std::endl;

		stud3.setSurname("Zzzzzzzzzzzzzzzz");
		stud3.setName("Zzzzzz");
		stud3.setLastname("Zzzzzzz");

		if (stud3 < stud2)
			std::cout << "stud3 < stud2" << std::endl;

		if (stud3 <= stud2)
			std::cout << "stud3 <= stud2" << std::endl;

		if (stud3 != stud2)
			std::cout << "stud3 != stud2" << std::endl;

		std::cin.get();
	}
	{
		List<int> list1;

		list1.pushInSortList(3);
		list1.pushInSortList(4);
		list1.pushInSortList(1);
		list1.pushInSortList(8);
		list1.pushInSortList(4);
		list1.pushInSortList(6);
		list1.pushInSortList(8);
		
		list1.print();

		List<int> list2(list1);
		list2.print();

		List<int> list3;
		list3 = list2;
		list3.print();

		for (int i = 0; i < 4; ++i)
			std::cout << ++list1 << ' ';

		std::cout << std::endl;

		list1.setCurrentNodeOnTheBegin();

		for (int i = 0; i < 4; ++i)
			std::cout << --list1 << ' ';

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