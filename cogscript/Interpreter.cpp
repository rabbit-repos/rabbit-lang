#include "pch.h"
#include "Interpreter.h"
#include "Config.h"
#include "CodeTokens.h"

Transpiler::Transpiler(ConstRef<Config> aConfiguration)
{
	myConfig = &aConfiguration;
}

Transpiler::~Transpiler()
{
}

InterpretationResult Transpiler::Interpret(ConstRef<CodeTokens> aCodeTokens) const
{
	ConstRef<VirtualList<Token>> list = aCodeTokens.GetTokens();
	for (i32 i = 0; i < list.Size(); ++i)
	{
		switch (list[i]->GetTokenID())
		{
		default:
			std::wcout << "Handle token " << static_cast<size>(list[i]->GetTokenID()) << L" Data(" << list[i]->GetContext().GetData() << L")" << std::endl;
			break;
			// TODO: Remove when no longer neccessary
#pragma warning ( suppress : 4065 )
		}
	}


	InterpretationResult result;
	result.ErrorMessage = StringData(L"Compiler Not Implemented");
	result.ErrorType = ErrorType::CompilerNotImplemented;
	return result;
}
