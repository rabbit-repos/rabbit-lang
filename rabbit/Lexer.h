#pragma once
#include "LexedCode.h"

class Lexer
{
public:
	Lexer(ConstRef<class Config> aConfig);
	~Lexer();

	LexedCode LexCode(StringData aCode);
	LexedCode LexFile(ConstRef<String> aFilePath);

private:
	void RemoveComments(Ref<StringData> aCode);

	ConstPtr<class Config> myConfig;
};
