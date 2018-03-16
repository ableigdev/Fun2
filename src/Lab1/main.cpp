#include <iostream>
#include <cstdlib>
#include <ctime>
#include "List.h"
#include "Student.h"

int main()
{

	{
		

		std::srand(time(0));

		List<int> list5;

		for (int i = 0; i < 1000000; ++i)
		{
			list5.pushBack(rand() % 100);
		}

	}

	std::cin.get();

	return 0;
}