#include "pch.h"
#include "Config.h"
#include "Tokenizer.h"
#include "Transpiler.h"
#include "Token.h"
#include "Stopwatch.h"

INT WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/,
	PSTR /*lpCmdLine*/, INT /*nCmdShow*/)
{
	LPWSTR *args;
	i32 argNum;

	args = CommandLineToArgvW(GetCommandLineW(), &argNum);
	if (args == nullptr)
	{
		wprintf(L"CommandLineToArgvW failed\n");
		return 0;
	}

	// Free memory allocated for CommandLineToArgvW arguments.

	
	PrintLine(L"Cog Language v0.0");

	if (argNum > 1)
	{
		if (String(L"run") == args[1])
		{
			Config config;

			if (argNum > 2)
			{
				if (String(L"help") == args[2])
				{
					PrintLine(L"Compiles and executes the project in the specified, or current directory.");
					PrintLine(L"Usage:");
					PrintLine(L"rbt -run [project-dir]");

					return 0;
				}
				else
				{
					PrintLine(L"Building and running project \"", String(StringData(args[2])), L"\"...");

					StringData projectPath = StringData(args[2]);
					config = Config(projectPath);
				}
			}
			else
			{
				PrintLine(L"Building and running project in the current directory...");
				config = Config(StringData(args[0]));
			}

			Tokenizer tokenizer(config);
			Transpiler interpreter(config);
			{
				Stopwatch watch;

				StringData code;
				CodeTokens codeTokens = tokenizer.TokenizeFile(L"helloworld/hello.cog", code, &watch);
				Const<float> time = watch.GetElapsedTimeInSeconds() * 1000.f;
				PrintLine(L"Tokenizer finished in ", time, L"ms");

				{
					Stopwatch interpretWatch;
					interpreter.Interpret(codeTokens);
					Const<float> interpretTime = watch.GetElapsedTimeInSeconds() * 1000.f;
					PrintLine(L"Interpreter finished in ", interpretTime, L"ms");
				}
				PrintLine(L"Compiler finished in ", watch.GetElapsedTimeInSeconds() * 1000.f, L"ms");
			}

			// ConstRef<List<StringData>> sourceFiles = config.GetSourceFiles();
			// for (i32 i = 0; i < sourceFiles.Size(); ++i)
			// 	tokenizer.TokenizeFile(sourceFiles[i]);

		}
		else
		{
			PrintLine(L"Unknown parameter: ", String(StringData(args[1])));
		}
	}

	LocalFree(args);

	return 0;
}
