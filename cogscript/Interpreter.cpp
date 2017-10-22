#include "pch.h"
#include "Interpreter.h"
#include "Config.h"
#include "CodeTokens.h"
#include "InterpreterContext.h"
#include "Namespace.h"
#include "KeywordID.h"

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
	return result;
}

void Interpreter::ParseGlobalScope(Ref<InterpreterContext> aContext) const
{
	switch (aContext.At().GetTokenID())
	{
	case TokenID::Text:
		ParseExpression(aContext);
		break;

	default:
		PrintLine(L"Handle token \"", aContext.At().TypeToString(), L"\" (Data = \"", aContext.ContextAt().GetData(), L"\")");
		break;
		// TODO: Remove when no longer neccessary
#pragma warning ( suppress : 4065 )
	}
}

void Interpreter::ParseExpression(Ref<InterpreterContext> aContext) const
{
	if (aContext.At().GetTokenID() == TokenID::Text)
	{
		Const<KeywordID> keyword = aContext.KeywordAt();

		switch (keyword)
		{
		case KeywordID::Global:
		case KeywordID::Pure:
		case KeywordID::Internal:
		case KeywordID::Type:
			// ParseType(aContext);
		case KeywordID::Object:
			ParseObject(aContext);
			break;

		default:
			// TODO: Remove the not implemented part of this when the language is done. See you in 10 years or more likely never as the compiler will most likely be rewritten from "scratch".
			aContext.ReportError(ErrorCode::UnexpectedKeyword, L"This keyword is not valid at this location or is not implemented.", 0);
			break;
		}
	}
}

void Interpreter::ParseObject(Ref<InterpreterContext> aContext) const
{
	aContext;
}
