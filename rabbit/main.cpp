#include "pch.h"
#include <iostream>
#include "StringData.h"
#include "String.h"
#include "Config.h"
#include "Lexer.h"
#include "Interpreter.h"
#include "Lexeme.h"

void Randomize(Const<RawPtr> aData, Const<size> aSize)
{
	std::random_device device;
	Const<std::uniform_int_distribution<size>> d(MinOf<size>, MaxOf<size>);

	Const<size> num = aSize / sizeof size;
	for (size i = 0; i < num; ++i)
	{
		Const<size> value = d(device);
		memcpy(&reinterpret_cast<Ptr<byte>>(aData)[i * sizeof size], &value, sizeof value);
	}

	Const<size> value = d(device);
	size remaining = aSize - num * sizeof size;
	if (remaining > 0)
		memcpy(&reinterpret_cast<Ptr<byte>>(aData)[aSize - remaining], &value, remaining);
}

#define TESTCLASS(CNAME, NumData) class CNAME : public Lexeme				\
{																			\
public:																		\
	CNAME() : myData(NumData)												\
	{																		\
		std::cout << #CNAME ## "::" ## #CNAME ## "()" << std::endl;			\
		Randomize(myData.GetAddress(), myData.SizeInBytes());				\
	}																		\
																			\
	CNAME(RValue<CNAME> aMove) : myData(std::move(aMove.myData)) { } 		\
																			\
	virtual void Test() override											\
	{																		\
		std::cout << #CNAME ## "::Test()" << std::endl;						\
	}																		\
																			\
	~CNAME()																\
	{																		\
		std::cout << #CNAME ## "::~" ## #CNAME ## "()" << std::endl;		\
	}																		\
																			\
private:																	\
	ResizableArray<byte> myData;											\
	void * someDataIOwn;													\
};

TESTCLASS(A, 23)
TESTCLASS(B, 4)
TESTCLASS(C, 83)
TESTCLASS(D, 86)
TESTCLASS(E, 54)
TESTCLASS(F, 80)
TESTCLASS(G, 59)
TESTCLASS(H, 20)
TESTCLASS(I, 40)
TESTCLASS(J, 92)

class Name
{
public:
	Name(StringData aName)
	{
		data = std::move(aName);
	}

private:
	StringData data;
};

i32 main(Const<i32> aArgNum, ConstPtr<char> aArgs[])
{
	Name one(StringData(L"One"));
	Name two = one;


	// {
	// 	LexedCode list;
	// 
	// 	std::random_device device;
	// 	Const<std::uniform_int_distribution<size>> d(0, 9);
	// 
	// 	for (size i = 0; i < 10; ++i)
	// 	{
	// 		Const<size> v = d(device);
	// 		switch (v)
	// 		{
	// 		case 0:
	// 			list.Add(A());
	// 			break;
	// 		case 1:
	// 			list.Add(B());
	// 			break;
	// 		case 2:
	// 			list.Add(C());
	// 			break;
	// 		case 3:
	// 			list.Add(D());
	// 			break;
	// 		case 4:
	// 			list.Add(E());
	// 			break;
	// 		case 5:
	// 			list.Add(F());
	// 			break;
	// 		case 6:
	// 			list.Add(G());
	// 			break;
	// 		case 7:
	// 			list.Add(H());
	// 			break;
	// 		case 8:
	// 			list.Add(I());
	// 			break;
	// 		case 9:
	// 			list.Add(J());
	// 			break;
	// 		}
	// 	}
	// 
	// }
	// 
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
			ConstRef<List<StringData>> sourceFiles = config.GetSourceFiles();
			for (i32 i = 0; i < sourceFiles.Size(); ++i)
				lexer.LexFile(sourceFiles[i]);

			lexer.LexFile(L"lexing/lexing.rbt");

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
