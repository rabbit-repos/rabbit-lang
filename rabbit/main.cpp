#include <iostream>
#include "json.h"

int main(int aArgNum, const char * aArgs[])
{
	std::cout << "Rabbit Language v.0" << std::endl;

	if (aArgNum > 1)
	{
		std::cout << aArgs[1] << std::endl;
	}

	std::cout << "Press Return to quit" << std::endl;
	std::cin.get();

	return 0;
}
