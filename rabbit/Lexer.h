#pragma once
#include "VirtualList.h"
#include "LexedCode.h"

class Lexer
{
public:
	Lexer(ConstRef<class Config> aConfig);
	~Lexer();

	LexedCode LexCode(Const<String> aCode);
	LexedCode LexFile(ConstRef<String> aFilePath);

private:
	ConstPtr<class Config> myConfig;
};
