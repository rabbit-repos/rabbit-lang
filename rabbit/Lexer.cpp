#include "pch.h"
#include "Lexer.h"

Lexer::Lexer(ConstRef<class Config> aConfig)
{
	myConfig = &aConfig;
}

Lexer::~Lexer()
{
}

ResizableArray<ConstPtr<class Lexeme>> Lexer::LexCode(StringData aCode)
{
	return ResizableArray<ConstPtr<class Lexeme>>();
}

ResizableArray<ConstPtr<class Lexeme>> Lexer::LexFile(ConstRef<String> aFilePath)
{
	std::wifstream f(aFilePath.ToWideString());
	
	StringData code;
	std::wstring line;
	while (std::getline(f, line))
	{
		code.Append(line.data(), static_cast<i32>(line.size()));
	}

	return LexCode(std::move(code));
}
