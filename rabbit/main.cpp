#include <iostream>
#include "json.h"
#include "MutableStringBlob.h"

int main(int aArgNum, const char * aArgs[])
{
	MutableStringBlob Text(L"Apor äter gröna legofigurer!");

	std::cout << "Rabbit Language v.0" << std::endl;

	if (aArgNum > 1)
	{
		if (strcmp("-run", aArgs[1]) == 0)
		{
			if (aArgNum > 2)
			{
				if (strcmp("help", aArgs[2]) == 0)
				{
					std::cout << "Compiles and executes the project in the specified, or current directory." << std::endl
						<< "Usage:" << std::endl
						<< "rbt -run [project-dir]" << std::endl;
				}
				else
				{
					std::cout << "Building and running directory \"" << aArgs[2] << "\"..." << std::endl;
				}
			}
			else
			{
				std::cout << "Building and running the current directory..." << std::endl;
			}
		}
		else
		{
			std::cout << "Unknown parameter: " << aArgs[1] << std::endl;
		}
	}

	std::cout << "Press Return to quit" << std::endl;
	std::cin.get();

	return 0;
}
