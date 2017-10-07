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
	static std::random_device device;
	static Const<std::uniform_int_distribution<size>> d(MinOf<size>, MaxOf<size>);

	Const<size> num = aSize / sizeof size;
	for (size i = 0; i < num; ++i)
	{
		Const<size> value = d(device);
		memcpy(&reinterpret_cast<Ptr<u8>>(aData)[i * sizeof size], &value, sizeof value);
	}

	Const<size> value = d(device);
	size remaining = aSize - num * sizeof size;
	if (remaining > 0)
		memcpy(&reinterpret_cast<Ptr<u8>>(aData)[aSize - remaining], &value, remaining);
}

#define TESTCLASS(CNAME, NumData) class CNAME : public Lexeme				\
{																			\
public:																		\
	CNAME() : myData(NumData)												\
	{																		\
		Randomize(myData.GetAddress(), myData.SizeInBytes());				\
	}																		\
																			\
	CNAME(ConstRef<CNAME> aCopy) : myData(aCopy.myData.Copy()) { }			\
	Ref<CNAME> operator=(ConstRef<CNAME> aCopy)								\
	{																		\
		myData = aCopy.myData.Copy();										\
		return *this;														\
	}																		\
																			\
	CNAME(RValue<CNAME> aMove) : myData(std::move(aMove.myData)) { } 		\
	Ref<CNAME> operator=(RValue<CNAME> aCopy)								\
	{																		\
		myData = std::move(aCopy.myData);									\
		return *this;														\
	}																		\
																			\
	virtual void AppendData(Ref<List<u8>> aData) override					\
	{																		\
		aData.AddRange(myData.GetAddress(), (i32)myData.Size());			\
	}																		\
																			\
	~CNAME()																\
	{																		\
	}																		\
																			\
private:																	\
	ResizableArray<u8> myData;												\
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

// size hashData()
// {
// 
// }

i32 main(Const<i32> aArgNum, ConstPtr<char> aArgs[])
{
	{
		std::default_random_engine device;
		device.seed(0);
		Const<std::uniform_int_distribution<size>> d(0, 9);

		for (;;)
		{
			std::vector<Lexeme*> vector;
			VirtualList list;

			for (i32 i = 0; i < 10000; ++i)
			{
				Const<size> v = d(device);
				switch (v)
				{
				case 0: {
					auto * a = new A();
					list.Add<A>(A(*a));
					vector.emplace_back(a);
				} break;
				case 1: {
					auto * a = new B();
					list.Add<B>(B(*a));
					vector.emplace_back(a);
				} break;
				case 2: {
					auto * a = new C();
					list.Add<C>(C(*a));
					vector.emplace_back(a);
				} break;
				case 3: {
					auto * a = new D();
					list.Add<D>(D(*a));
					vector.emplace_back(a);
				} break;
				case 4: {
					auto * a = new E();
					list.Add<E>(E(*a));
					vector.emplace_back(a);
				} break;
				case 5: {
					auto * a = new F();
					list.Add<F>(F(*a));
					vector.emplace_back(a);
				} break;
				case 6: {
					auto * a = new G();
					list.Add<G>(G(*a));
					vector.emplace_back(a);
				} break;
				case 7: {
					auto * a = new H();
					list.Add<H>(H(*a));
					vector.emplace_back(a);
				} break;
				case 8: {
					auto * a = new I();
					list.Add<I>(I(*a));
					vector.emplace_back(a);
				} break;
				case 9: {
					auto * a = new J();
					list.Add<J>(J(*a));
					vector.emplace_back(a);
				} break;
				}

				// std::cout << i << std::endl;
			}

			List<u8> totalDataControl;
			List<u8> totalDataVirtual;

			for (size_t i = 0; i < vector.size(); ++i)
			{
				vector[i]->AppendData(totalDataControl);
				delete vector[i];
			}
			for (i32 i = 0; i < list.Size(); ++i)
				list[i]->AppendData(totalDataVirtual);

			if (totalDataControl.Size() != totalDataVirtual.Size())
				abort();
			if (memcmp(totalDataControl.GetAddress(), totalDataVirtual.GetAddress(), totalDataControl.Size()) != 0)
				abort();

			// static i32 i = 0;
			// std::cout << "it " << ++i << std::endl;
		}
	}

	std::cout << "Done" << std::endl;
	std::cin.get();

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
