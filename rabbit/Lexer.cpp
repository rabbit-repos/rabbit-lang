#include "pch.h"
#include "Lexer.h"
#include "Lexeme.h"
#include "CharUtility.h"
#include "LexingContext.h"

Lexer::Lexer(ConstRef<class Config> aConfig)
{
	myConfig = &aConfig;
}

Lexer::~Lexer()
{
}

template <typename TConditionChecker>
static String ParseUntil(Ref<LexingContext> aContext, ConstRef<TConditionChecker> aContinueCondition)
{
	i32 length = 0;
	while (!aContext.IsAtEnd() && aContinueCondition(aContext.At(length)))
		++length;
	String str = aContext.Peek(length);
	aContext.AdvanceCursor(length);
	return str;
}

template <typename TConditionChecker>
static String ParseUntilString(Ref<LexingContext> aContext, ConstRef<String> aString)
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

LexedCode Lexer::LexCode(ConstRef<StringData> aCode)
{
	LexedCode lexemes;
	LexingContext context(&aCode);

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
			std::wcout << L"Lexer did not progress at: \"" << context.Peek(5) << "\"..." << std::endl;
			abort();
		}
	}

	return lexemes;
}

void Lexer::ParseComment(Ref<LexingContext> aContext)
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

void Lexer::ParseCompilerDirective(Ref<LexingContext> aContext)
{
	if (aContext.At() != L'#')
		return;

	String directiveName = ParseLexeme(aContext);
	std::wcout << L"Compiler Directive: \"" << directiveName << L"\"" << std::endl;
}

void Lexer::ParseNumberLiteral(Ref<LexingContext> aContext)
{
	if (!CharUtility::IsDigit(aContext.At()))
		return;

	Const<String> number = ParseUntil(aContext, [](Const<Char> aChar) { return CharUtility::IsDigit(aChar); });
	std::wcout << L"Literal Number: " << number << std::endl;
}

// TODO: Rewrite using ParseUntil
void Lexer::ParseStringLiteral(Ref<LexingContext> aContext)
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

void Lexer::ParseUnknownStatement(Ref<LexingContext> aContext)
{
	String statement = ParseLexeme(aContext);

	if (statement.Size() > 0)
		std::wcout << L"Statement: \"" << statement << L"\"" << std::endl;
}

String Lexer::ParseLexeme(Ref<LexingContext> aContext)
{
	i32 length = 0;
	while (!aContext.IsAtEnd() && CharUtility::IsValidLexemeCharacter(aContext.At(length), length == 0))
		++length;
	String str = aContext.Peek(length);
	aContext.AdvanceCursor(length);
	return str;
}

LexedCode Lexer::LexFile(ConstRef<String> aFilePath)
{
	std::wifstream f(aFilePath.ToWideString());
	
	if (!f.good())
	{
		std::wcout << L"Failed to open file " << aFilePath << std::endl;
		return LexedCode();
	}

	StringData code;
	std::wstring line;
	while (std::getline(f, line))
	{
		code.Append(line.data(), static_cast<i32>(line.size()));
		code.AppendChar(L'\n');
	}

	return LexCode(std::move(code));
}
