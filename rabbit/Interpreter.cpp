#include "pch.h"
#include "Interpreter.h"
#include "Config.h"
#include "CodeTokens.h"
#include "NotImplementedToken.h"

Interpreter::Interpreter(ConstRef<Config> aConfiguration)
{
	myConfig = &aConfiguration;
}

Interpreter::~Interpreter()
{
}

InterpretationResult Interpreter::Interpret(ConstRef<CodeTokens> aCodeTokens) const
{
	ConstRef<VirtualList<Token>> list = aCodeTokens.GetTokens();
	for (i32 i = 0; i < list.Size(); ++i)
	{
		if (list[i]->GetTokenID() == TokenID::None)
		{
			std::wcout << "TokenizerNotImplemented: \"" << static_cast<Ptr<NotImplementedToken>>(list[i])->GetTokenString() << L"\"" << std::endl;
		}
		else
		{
			switch (aCodeTokens.GetTokens()[i]->GetTokenID())
			{
			default:
				std::wcout << "Handle token " << static_cast<size>(aCodeTokens.GetTokens()[i]->GetTokenID()) << std::endl;
				break;
				// TODO: Remove when no longer neccessary
#pragma warning ( suppress : 4065 )
			}
		}
	}


	InterpretationResult result;
	result.ErrorMessage = StringData(L"Compiler Not Implemented");
	result.ErrorType = ErrorType::CompilerNotImplemented;
	return result;
}
