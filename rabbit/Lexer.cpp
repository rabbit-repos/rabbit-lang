#include "pch.h"
#include "Lexer.h"
#include "Lexeme.h"

Lexer::Lexer(ConstRef<class Config> aConfig)
{
	myConfig = &aConfig;
}

Lexer::~Lexer()
{
}

LexedCode Lexer::LexCode(StringData aCode)
{
	LexedCode lexemes;

	return lexemes;
}

LexedCode Lexer::LexFile(ConstRef<String> aFilePath)
{
	std::wifstream f(aFilePath.ToWideString());
	
	StringData code;
	std::wstring line;
	while (std::getline(f, line))
	{
		code.Append(line.data(), static_cast<i32>(line.size()));
		// code.AppendChar(L'\r');
		code.AppendChar(L'\n');
	}

	return LexCode(std::move(code));
}
