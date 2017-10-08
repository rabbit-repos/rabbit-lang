#include "pch.h"
#include "Tokenizer.h"
#include "Token.h"
#include "CharUtility.h"
#include "TokenizerContext.h"

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
	while (!aContext.IsAtEnd() && aContinueCondition(aContext.At(length)))
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
	TokenizerContext context(&aCode);

	while (!context.IsAtEnd())
	{
		Const<i32> initialLocation = context.CursorLocation();

		if (CharUtility::IsWhiteSpace(context.At()))
		{
			context.AdvanceCursor();
			continue;
		}

		switch (context.At())
		{
		case L'/':
			ParseComment(context);
			break;
		case L'#':
			ParseCompilerDirective(context);
			break;
		case L'"':
			ParseStringLiteral(context);
			break;
		case L'!':
			std::wcout << L"NOT Statement: \"!\"" << std::endl;
			context.AdvanceCursor();
			break;
		case L'-':
			std::wcout << L"Negation Statement: \"-\"" << std::endl;
			context.AdvanceCursor();
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

void Tokenizer::ParseComment(Ref<TokenizerContext> aContext)
{
	if (aContext.At() != L'/')
		return;

	if (aContext.At(1) == L'/')
	{
		ParseUntil(aContext, [](Char aChar) { return aChar != L'\n'; } );
	}
	else if (aContext.At(1) == L'*')
	{
		aContext.AdvanceCursor(2);

		do
		{
			aContext.AdvanceCursor();
		} while (aContext.Peek(2) == L"*/" && !aContext.IsAtEnd());
	}
}

void Tokenizer::ParseCompilerDirective(Ref<TokenizerContext> aContext)
{
	if (aContext.At() != L'#')
		return;

	String directiveName = ParseLexeme(aContext);
	std::wcout << L"Compiler Directive: \"" << directiveName << L"\"" << std::endl;
}

void Tokenizer::ParseNumberLiteral(Ref<TokenizerContext> aContext)
{
	if (!CharUtility::IsDigit(aContext.At()))
		return;

	Const<String> number = ParseUntil(aContext, [](Const<Char> aChar) { return CharUtility::IsDigit(aChar); });
	std::wcout << L"Literal Number: " << number << std::endl;
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

	std::wcout << L"String literal: \"" << aContext.Peek(length) << L"\"" << std::endl;

	aContext.AdvanceCursor(length + 1);
}

void Tokenizer::ParseUnknownStatement(Ref<TokenizerContext> aContext)
{
	String statement = ParseLexeme(aContext);

	if (statement.Size() > 0)
		std::wcout << L"Statement: \"" << statement << L"\"" << std::endl;
}

String Tokenizer::ParseLexeme(Ref<TokenizerContext> aContext)
{
	i32 length = 0;
	while (!aContext.IsAtEnd() && CharUtility::IsValidLexemeCharacter(aContext.At(length), length == 0))
		++length;
	String str = aContext.Peek(length);
	aContext.AdvanceCursor(length);
	return str;
}

CodeTokens Tokenizer::TokenizeFile(ConstRef<String> aFilePath)
{
	std::wifstream f(aFilePath.ToWideString());
	
	if (!f.good())
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

	return TokenizeCode(std::move(code));
}
