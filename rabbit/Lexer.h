#pragma once
#include "VirtualList.h"

class Lexer
{
public:
	Lexer(ConstRef<class Config> aConfig);
	~Lexer();

	VirtualList LexCode(StringData aCode);
	VirtualList LexFile(ConstRef<String> aFilePath);

private:
	void RemoveComments(Ref<StringData> aCode);

	ConstPtr<class Config> myConfig;
};
