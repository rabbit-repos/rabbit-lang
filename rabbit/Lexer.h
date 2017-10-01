#pragma once
#include "ResizableArray.h"
#include "StringData.h"
#include "String.h"

class Lexer
{
public:
	Lexer(ConstRef<class Config> aConfig);
	~Lexer();

	ResizableArray<ConstPtr<class Lexeme>> LexCode(StringData aCode);
	ResizableArray<ConstPtr<class Lexeme>> LexFile(ConstRef<String> aFilePath);

private:
	void RemoveComments(Ref<StringData> aCode);

	ConstPtr<class Config> myConfig;
};
