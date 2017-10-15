#include "pch.h"
#include "Tokenizer.h"
#include "Token.h"
#include "CharUtility.h"
#include "TokenizerContext.h"
#include "SpecialTokenMap.h"
#include "NotImplementedToken.h"
#include "Stopwatch.h"
#include <thread>
#include "TokenID.h"

static SpecialTokenMap<TokenID> CreateSpecialTokens();
static Const<SpecialTokenMap<TokenID>> gSpecialTokens = CreateSpecialTokens();

SpecialTokenMap<TokenID> CreateSpecialTokens()
{
	SpecialTokenMap<TokenID> specialTokens;
	specialTokens[L"::"] = TokenID::ScopeOperator;
	specialTokens[L"++"] = TokenID::Incrementation;
	specialTokens[L"--"] = TokenID::Decrementation;
	specialTokens[L"<<"] = TokenID::BitShiftLeft; // Will also assign StreamOutput
	specialTokens[L">>"] = TokenID::BitShiftRight; // Will also assign StreamInput
	specialTokens[L">"] = TokenID::ClosingAngleBracket;
	specialTokens[L"<"] = TokenID::OpeningAngleBracket;
	specialTokens[L"!"] = TokenID::OpeningAngleBracket;
	specialTokens[L"-"] = TokenID::Hyphen;
	return specialTokens;
}

Tokenizer::Tokenizer(ConstRef<class Config> aConfig)
{
	myConfig = &aConfig;
}

Tokenizer::~Tokenizer()
{
}

template <typename TConditionChecker>
static String ParseUntil(Ref<TokenizerContext> aContext, ConstRef<TConditionChecker> aContinueCondition)
{
	i32 length = 0;
	while (!aContext.IsAtEnd() && aContinueCondition(length))
		++length;
	String str = aContext.Peek(length);
	aContext.AdvanceCursor(length);
	return str;
}

template <typename TConditionChecker>
static String ParseUntilString(Ref<TokenizerContext> aContext, ConstRef<String> aString)
{
	i32 length = 0;
	while (!aContext.IsAtEnd())
	{
		if (aContext.StringAt(length, aString.Size()) == aString)
			break;
		++length;
	}
	String str = aContext.Peek(length);
	aContext.AdvanceCursor(length);
	return str;
}

CodeTokens Tokenizer::TokenizeCode(ConstRef<StringData> aCode)
{
	CodeTokens tokens;
	TokenizerContext context(&aCode, tokens);

	while (!context.IsAtEnd())
	{
		Const<i32> initialLocation = context.CursorLocation();

		if (CharUtility::IsWhiteSpace(context.At()))
		{
			context.AdvanceCursor();
			continue;
		}

		if (context.At() == L'-')
			ParseComment(context);

		Const<i32> startSpecial = context.CursorLocation();
		String specialTokenString;
		// TODO: Find out if this can/should be better optimized
		Const<TokenID> specialToken = TryReadSpecialToken(context, specialTokenString);

		if (specialToken != TokenID::None)
		{
			tokens.AddToken<NotImplementedToken>(NotImplementedToken(TokenID::None, specialTokenString));
			// std::wcout << L"Special Token: \"" << String(aCode).SubString(startSpecial, context.CursorLocation() - startSpecial) << L"\"" << std::endl;
			continue;
		}

		switch (context.At())
		{
		case L'#':
			ParseCompilerDirective(context);
			break;
		case L'"':
			ParseStringLiteral(context);
			break;
		case L'0':
		case L'1':
		case L'2':
		case L'3':
		case L'4':
		case L'5':
		case L'6':
		case L'7':
		case L'8':
		case L'9':
			ParseNumberLiteral(context);
			break;
		default:
			ParseUnknownStatement(context);
		}

		if (context.CursorLocation() == initialLocation)
		{
			std::wcout << L"Tokenizer did not progress at: \"" << context.Peek(5) << L"\"..." << std::endl;
			abort();
		}
	}

	return tokens;
}

TokenID Tokenizer::TryReadSpecialToken(Ref<TokenizerContext> aContext, Out<String> aSpecialTokenFound)
{
	Const<i32> maxDepth = gSpecialTokens.GetDepth();
	ConstPtr<SpecialTokenMap<TokenID>> current = &gSpecialTokens;
	for (i32 i = 0; i < maxDepth && current != null; ++i)
	{
		if (current->GetOurValue() != TokenID::None)
		{
			Const<TokenID> specialToken = current->GetOurValue();
			aSpecialTokenFound = aContext.Peek(i);
			aContext.AdvanceCursor(i);
			return specialToken;
		}
		current = current->TryGetNextLayer(aContext.At(i));
	}
	return TokenID::None;
}

void Tokenizer::ParseComment(Ref<TokenizerContext> aContext)
{
	if (aContext.Peek(2) != L"--")
		return;

	if (aContext.StringAt(2, 2) == L"[[")
	{
		ParseUntil(aContext, [&aContext](Const<i32> aIndex) { return aContext.StringAt(aIndex, 2) == L"]]"; } );
	}
	else
	{
		aContext.AdvanceCursor(2);
		ParseUntil(aContext, [&aContext](Const<i32> aIndex) { return aContext.At(aIndex) != L'\n'; });
	}
}

void Tokenizer::ParseCompilerDirective(Ref<TokenizerContext> aContext)
{
	if (aContext.At() != L'#')
		return;

	String directiveName = ParseToken(aContext);
	StringData data(L"Compiler Directive Parsing (Data = \"");
	data.Append(directiveName);
	data.Append(L"\")");
	aContext.AddToken<NotImplementedToken>(NotImplementedToken(TokenID::CompilerDirective, std::move(data)));
	// std::wcout << L"Compiler Directive: \"" << directiveName << L"\"" << std::endl;
}

void Tokenizer::ParseNumberLiteral(Ref<TokenizerContext> aContext)
{
	if (!CharUtility::IsDigit(aContext.At())) 
		return;

	Const<String> number = ParseUntil(aContext, [&aContext](Const<i32> aIndex) { return CharUtility::IsDigit(aContext.At(aIndex)); });
	// std::wcout << L"Literal Number: " << number << std::endl;
	StringData data(L"Number Literal Parsing (Data = \"");
	data.Append(number);
	data.Append(L"\")");
	aContext.AddToken<NotImplementedToken>(NotImplementedToken(TokenID::NumberLiteral, std::move(data)));
}

// TODO: Rewrite using ParseUntil
void Tokenizer::ParseStringLiteral(Ref<TokenizerContext> aContext)
{
	if (aContext.At() != L'"')
		return;

	aContext.AdvanceCursor();

	i32 length = 0;
	bool isEscaping = false;
	do 
	{
		isEscaping = aContext.At(length) == L'\\';
		if (isEscaping)
			++length;
		++length;
	} while (aContext.At(length) != L'"' || isEscaping && !aContext.IsAtEnd());

	// std::wcout << L"String literal: \"" << aContext.Peek(length) << L"\"" << std::endl;
	StringData data(L"String Literal Parsing (Data = \"");
	data.Append(aContext.Peek(length));
	data.Append(L"\")");
	aContext.AddToken<NotImplementedToken>(NotImplementedToken(TokenID::StringLiteral, std::move(data)));

	aContext.AdvanceCursor(length + 1);
}

void Tokenizer::ParseUnknownStatement(Ref<TokenizerContext> aContext)
{
	String statement = ParseToken(aContext);

	if (statement.Size() > 0)
	{
		StringData data(L"Unhandled Statement ( Data = \"");
		data.Append(statement);
		data.Append(L"\")");
		aContext.AddToken<NotImplementedToken>(NotImplementedToken(TokenID::None, std::move(data)));
	}
}

String Tokenizer::ParseToken(Ref<TokenizerContext> aContext)
{
	if (CharUtility::IsValidFirstSymbolCharacter(aContext.At()))
	{
		i32 length = 0;
		while (!aContext.IsAtEnd() && CharUtility::IsValidLexemeCharacter(aContext.At(length), length == 0))
			++length;
		String str = aContext.Peek(length);
		aContext.AdvanceCursor(length);
		return str;
	}
	else
	{
		// NOTE: We can't create a string from aContext.At() since that string would have to reference a local variable
		String str = aContext.Peek(1);
		aContext.AdvanceCursor();
		return str;
	}
}

CodeTokens Tokenizer::TokenizeFile(ConstRef<String> aFilePath, Ptr<Stopwatch> aWatchToRestartWhenFileIsRead /*= null*/)
{
	std::wifstream f(aFilePath.ToWideString());
	
	if (f.good())
	{
		std::wcout << aFilePath << std::endl;
		std::wcout.flush();
	}
	else
	{
		std::wcout << L"Failed to open file " << aFilePath << std::endl;
		return CodeTokens();
	}

	StringData code;
	std::wstring line;
	while (std::getline(f, line))
	{
		code.Append(line.data(), static_cast<i32>(line.size()));
		code.AppendChar(L'\n');
	}

	if (aWatchToRestartWhenFileIsRead)
		aWatchToRestartWhenFileIsRead->Restart();
	
	return TokenizeCode(code);
}
