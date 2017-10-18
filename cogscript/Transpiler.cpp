#include "pch.h"
#include "Transpiler.h"
#include "Config.h"
#include "CodeTokens.h"
#include "TranspilerContext.h"

Transpiler::Transpiler(ConstRef<Config> aConfiguration)
{
	myConfig = &aConfiguration;
}

Transpiler::~Transpiler()
{
}

InterpretationResult Transpiler::Interpret(ConstRef<CodeTokens> aCodeTokens) const
{
	TranspilerContext context(aCodeTokens);
	
	do
	{
		Const<i32> beginCursor = context.GetCursorLocation();

		ParseGlobalScope(context);

		Const<i32> endCursor = context.GetCursorLocation();
		if (endCursor == beginCursor)
		{
			PrintLine(L"Transpiler did not progress at token \"", context.At().ToString(), L"\" (Data = \"", context.At().GetContext().GetData(), L"\")");
			abort();
		}
	} while (!context.IsAtEnd());


	InterpretationResult result;
	result.ErrorMessage = StringData(L"Compiler Not Implemented");
	result.ErrorType = ErrorType::CompilerNotImplemented;
	return result;
}

void Transpiler::ParseGlobalScope(ConstRef<TranspilerContext> aContext) const
{
	switch (aContext.At().GetTokenID())
	{
	default:
		PrintLine("Handle token ", static_cast<size>(aContext.At().GetTokenID()), L" Data(", aContext.At().GetContext().GetData(), L")");;
		break;
		// TODO: Remove when no longer neccessary
#pragma warning ( suppress : 4065 )
	}
}
