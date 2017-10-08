#include "pch.h"
#include <iostream>
#include "StringData.h"
#include "String.h"
#include "Config.h"
#include "Lexer.h"
#include "Interpreter.h"
#include "Lexeme.h"

i32 main(Const<i32> aArgNum, ConstPtr<char> aArgs[])
{
	std::cout << "Rabbit Language v0.0" << std::endl;

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

					StringData projectPath = StringData::FromASCII(aArgs[2]);
					config = Config(projectPath);
				}
			}
			else
			{
				std::cout << "Building and running project in the current directory..." << std::endl;
				config = Config(StringData::FromASCII(aArgs[0]));
			}

			Lexer lexer(config);
			Interpreter interpreter(config);
			LexedCode lexedCode = lexer.LexFile(L"lexing/lexing.rbt");
			interpreter.Interpret(lexedCode);

			// ConstRef<List<StringData>> sourceFiles = config.GetSourceFiles();
			// for (i32 i = 0; i < sourceFiles.Size(); ++i)
			// 	lexer.LexFile(sourceFiles[i]);

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
