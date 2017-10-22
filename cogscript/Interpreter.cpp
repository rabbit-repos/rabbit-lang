#include "pch.h"
#include "Interpreter.h"
#include "Config.h"
#include "CodeTokens.h"
#include "InterpreterContext.h"
#include "Namespace.h"
#include "KeywordID.h"
#include "TypeModifiers.h"
#include "ObjectSymbol.h"

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
			PrintLine(L"Interpreter did not progress at \"", context.At().GetContext().GetData(), L"\" (Token ID = ", context.At().TypeToString(), L")");
			FatalError();
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
		ParseDeclaration(aContext);
		break;

	default:
		PrintLine(L"Handle token \"", aContext.At().TypeToString(), L"\" (Data = \"", aContext.ContextAt().GetData(), L"\")");
		break;
		// TODO: Remove when no longer neccessary
#pragma warning ( suppress : 4065 )
	}
}

void Interpreter::ParseDeclaration(Ref<InterpreterContext> aContext) const
{
	if (aContext.At().GetTokenID() == TokenID::Text)
	{
		Const<TypeModifiers> modifiers = ParseTypeModifiers(aContext);

		Const<KeywordID> keyword = aContext.KeywordAt();
		switch (keyword)
		{
		case KeywordID::Object:
			ParseObject(aContext, modifiers);
			break;

		default:
			PrintLine(L"Declarations using", static_cast<i32>(keyword), L" is not implemented");
			FatalError();
			break;
		}
	}
}

TypeModifiers Interpreter::ParseTypeModifiers(Ref<InterpreterContext> aContext) const
{
	TypeModifiers modifiers = TypeModifiers::None;
	
	i32 i = 0;
	do
	{
		switch (aContext.KeywordAt())
		{
		case KeywordID::Global:
			modifiers |= TypeModifiers::Global;
			aContext.AdvanceCursor();
			break;
		case KeywordID::Internal:
			modifiers |= TypeModifiers::Internal;
			aContext.AdvanceCursor();
			break;

		default:
			return modifiers;
		}
		++i;
	} while (!aContext.IsAtEnd());

	return modifiers;
}

Ref<ObjectSymbol> Interpreter::ParseObject(Ref<InterpreterContext> aContext, TypeModifiers aModifiers) const
{
	// Default objects to internal scope
	if (!FlagIsSet(aModifiers, TypeModifiers::Global))
		SetFlag(aModifiers, TypeModifiers::Internal);

#ifdef _DEBUG
	if (FlagIsSet(aModifiers, TypeModifiers::Global) && FlagIsSet(aModifiers, TypeModifiers::Internal))
	{
		PrintLine(L"Object is marked as both global and internal");
		FatalError();
	}
#endif

	ObjectSymbol newSymbol(aContext.ContextAt().GetData());
	
	aContext.AdvanceCursor();

	// Parse declarations

	return aContext.GetGlobalNamespace().AddSymbol(std::move(newSymbol));
}
