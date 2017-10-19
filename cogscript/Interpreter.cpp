#include "pch.h"
#include "Interpreter.h"
#include "Config.h"
#include "CodeTokens.h"
#include "InterpreterContext.h"

Interpreter::Interpreter(ConstRef<Config> aConfiguration)
{
	myConfig = &aConfiguration;
}

Interpreter::~Interpreter()
{
}

InterpretationResult Interpreter::Interpret(ConstRef<CodeTokens> aCodeTokens) const
{
	InterpreterContext context(aCodeTokens);
	
	do
	{
		Const<i32> beginCursor = context.GetCursorLocation();

		ParseGlobalScope(context);

		Const<i32> endCursor = context.GetCursorLocation();
		if (endCursor == beginCursor)
		{
			PrintLine(L"Interpreter did not progress at token \"", context.At().TypeToString(), L"\" (Data = \"", context.At().GetContext().GetData(), L"\")");
			abort();
		}
	} while (!context.IsAtEnd());


	InterpretationResult result;
	result.ErrorMessage = StringData(L"Compiler Not Implemented");
	result.ErrorType = ErrorType::CompilerNotImplemented;
	return result;
}

void Interpreter::ParseGlobalScope(ConstRef<InterpreterContext> aContext) const
{
	switch (aContext.At().GetTokenID())
	{
	default:
		PrintLine(L"Handle token \"", aContext.At().TypeToString(), L"\" (Data = \"", aContext.At().GetContext().GetData(), L"\")");
		break;
		// TODO: Remove when no longer neccessary
#pragma warning ( suppress : 4065 )
	}
}
