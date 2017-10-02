#include "pch.h"
#include <iostream>
#include "StringData.h"
#include "String.h"
#include "Config.h"
#include "Lexer.h"
#include "Interpreter.h"
#include "SymbolFilter.h"

i32 main(Const<i32> aArgNum, ConstPtr<char> aArgs[])
{
	for (;;)
	{
		SymbolFilter<int> symbolFilter;
		symbolFilter.GetOrCreateValue(L"apor-_aaa") = 100;
		symbolFilter.GetOrCreateValue(L"apor-_aaa2") = 200;
		symbolFilter.GetOrCreateValue(L"opa") = 300;
	
		std::cout << symbolFilter[L"apor-_aaa"] << std::endl;
		std::cout << symbolFilter[L"inget"] << std::endl;
		std::cout << symbolFilter[L"opa"] << std::endl;
	}
	
	// std::cin.get();

	std::cout << "Rabbit Language v.0" << std::endl;

	if (aArgNum > 1)
	{
		if (strcmp("-run", aArgs[1]) == 0)
		{
			Config config;

			if (aArgNum > 2)
			{
				if (strcmp("help", aArgs[2]) == 0)
				{
					std::cout << "Compiles and executes the project in the specified, or current directory." << std::endl
						<< "Usage:" << std::endl
						<< "rbt -run [project-dir]" << std::endl;

					return 0;
				}
				else
				{
					std::cout << "Building and running project \"" << aArgs[2] << "\"..." << std::endl;
					
					StringData data = StringData::FromASCII(aArgs[2]);
					String s = data; 

					config.OpenProject(s);
				}
			}
			else
			{
				std::cout << "Building and running project in the current directory..." << std::endl;
				config.OpenProject(StringData::FromASCII(aArgs[0]));
			}

			Lexer lexer(config);
			Interpreter interpreter(config);
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
