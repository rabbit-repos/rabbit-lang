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

LexedCode Lexer::LexCode(Const<String> aCode)
{
	LexedCode lexemes;
	
	return lexemes;
}

LexedCode Lexer::LexFile(ConstRef<String> aFilePath)
{
	std::wifstream f(aFilePath.ToWideString());
	
	if (!f.good())
	{
		std::wcout << "Failed to open file " << aFilePath << std::endl;
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
