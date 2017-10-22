#include "pch.h"
#include "Interpreter.h"
#include "Config.h"
#include "CodeTokens.h"
#include "InterpreterContext.h"
#include "Namespace.h"
#include "KeywordMap.h"
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

static KeywordMap GetKeywords();
static Const<KeywordMap> gKeywords(GetKeywords());

void Interpreter::ParseExpression(Ref<InterpreterContext> aContext) const
{
	ConstRef<Token> at = aContext.At();
	if (at.GetTokenID() == TokenID::Text)
	{
		ConstPtr<KeywordID> keyword = gKeywords.TryGetValue(aContext.At().GetContextData());

		switch (keyword != null ? *keyword : KeywordID::Unknown)
		{
			case KeywordID::
			ParseObject(aContext);
			break;

		default:
			aContext.ReportError(ErrorCode::UnexpectedKeyword, L"This keyword is not valid at this location.", 0);
			break;
		}
	}
}

void Interpreter::ParseObject(Ref<InterpreterContext> aContext) const
{
	aContext;
}

KeywordMap GetKeywords()
{
	KeywordMap keywords;
	keywords[L"type"] = KeywordID::Type;
	keywords[L"global"] = KeywordID::Global;
	keywords[L"event"] = KeywordID::Event;
	keywords[L"inherits"] = KeywordID::Inherits;
	keywords[L"requires"] = KeywordID::Requires;
	keywords[L"end"] = KeywordID::End;
	keywords[L"function"] = KeywordID::Function;
	keywords[L"internal"] = KeywordID::Internal;
	keywords[L"return"] = KeywordID::Return;
	keywords[L"returns"] = KeywordID::Returns;
	keywords[L"alias"] = KeywordID::Alias;
	keywords[L"mutable"] = KeywordID::Mutable;
	keywords[L"static"] = KeywordID::Static;
	keywords[L"flow_control"] = KeywordID::FlowControl;
	keywords[L"skip_when"] = KeywordID::SkipWhen;
	keywords[L"repeat_when"] = KeywordID::RepeatWhen;
	keywords[L"mixin"] = KeywordID::Mixin;
	return keywords;
}
