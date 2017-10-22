#include "pch.h"
#include "Tokenizer.h"
#include "Token.h"
#include "CharUtility.h"
#include "TokenizerContext.h"
#include "SpecialTokenMap.h"
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
	while (!aContext.IsAtEnd() && !aContinueCondition(length))
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

		if (specialTokenString.Size() > 0)
		{
			tokens.AddToken(Token(TokenID::Invalid, TokenContext(specialTokenString)));
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
			PrintLine(L"Tokenizer did not progress at: \"", context.Peek(5), L"\"...");
			FatalError();
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
		if (current->GetOurValue() < TokenID::Count)
		{
			Const<TokenID> specialToken = current->GetOurValue();
			aSpecialTokenFound = aContext.Peek(i);
			aContext.AdvanceCursor(i);
			return specialToken;
		}
		current = current->TryGetNextLayer(aContext.At(i));
	}
	return TokenID::Invalid;
}

void Tokenizer::ParseComment(Ref<TokenizerContext> aContext)
{
	if (aContext.Peek(2) != L"--")
		return;

	if (aContext.StringAt(2, 2) == L"[[")
	{
		ParseUntil(aContext, [&aContext](Const<i32> aIndex) { return aContext.StringAt(aIndex, 2) == L"]]"; });
		aContext.AdvanceCursor(2);
	}
	else
	{
		aContext.AdvanceCursor(2);
		ParseUntil(aContext, [&aContext](Const<i32> aIndex) { return aContext.At(aIndex) == L'\n'; });
	}
}

void Tokenizer::ParseCompilerDirective(Ref<TokenizerContext> aContext)
{
	if (aContext.At() != L'#')
		return;

	String directiveName = ParseToken(aContext);
	aContext.AddToken(Token(TokenID::CompilerDirective, directiveName));
	// std::wcout << L"Compiler Directive: \"" << directiveName << L"\"" << std::endl;
}

void Tokenizer::ParseNumberLiteral(Ref<TokenizerContext> aContext)
{
	if (!CharUtility::IsDigit(aContext.At())) 
		return;

	Const<String> number = ParseUntil(aContext, [&aContext](Const<i32> aIndex) { return CharUtility::IsDigit(aContext.At(aIndex)); });
	aContext.AddToken(Token(TokenID::NumberLiteral, TokenContext(number)));
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

	aContext.AddToken(Token(TokenID::StringLiteral, aContext.Peek(length)));

	aContext.AdvanceCursor(length + 1);
}

void Tokenizer::ParseUnknownStatement(Ref<TokenizerContext> aContext)
{
	if (CharUtility::IsWhiteSpace(aContext.At()))
	{
		ParseUntil(aContext, [&aContext](Const<i32> aOffset) { return CharUtility::IsWhiteSpace(aContext.At(aOffset)); });
		
		return;
	}

	String statement = ParseToken(aContext);

	if (statement.Size() > 0)
		aContext.AddToken(Token(TokenID::Text, statement));
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

CodeTokens Tokenizer::TokenizeFile(ConstRef<String> aFilePath, Ref<StringData> aFileContent, Ptr<Stopwatch> aWatchToRestartWhenFileIsRead /*= null*/)
{
	std::wifstream f(aFilePath.ToWideString());
	
	if (f.good())
	{
		PrintLine(aFilePath);
	}
	else
	{
		PrintLine(L"Failed to open file ", aFilePath);
		return CodeTokens();
	}

	std::wstring line;
	while (std::getline(f, line))
	{
		aFileContent.Append(line.data(), static_cast<i32>(line.size()));
		aFileContent.AppendChar(L'\n');
	}

	if (aWatchToRestartWhenFileIsRead)
		aWatchToRestartWhenFileIsRead->Restart();
	
	return TokenizeCode(aFileContent);
}
