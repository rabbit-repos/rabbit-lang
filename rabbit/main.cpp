#include <iostream>
#include "json.h"
#include "StringData.h"
#include "String.h"
#include "List.h"

void CompileProject(String ProjectPath);

int main(int aArgNum, const char * aArgs[])
{
	{
		List<i32> list;
		list.Add(10);
		list.Add(15);
		list.Add(5);

		for (i32 i = 0; i < list.Length(); ++i)
		{
			std::cout << list[i] << std::endl;
		}
	}

	{
		StringData Text(L"Apor äter gröna legofigurer!");
	}

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
					CompileProject(StringData::FromASCII(aArgs[2]));
				}
			}
			else
			{
				std::cout << "Building and running the current directory..." << std::endl;
				CompileProject(StringData::FromASCII(aArgs[0]));
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

void CompileProject(String ProjectPath)
{

}
