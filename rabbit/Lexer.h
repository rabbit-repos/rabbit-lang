#pragma once
#include "VirtualList.h"
#include "LexedCode.h"

class LexingContext;

class Lexer
{
public:
	Lexer(ConstRef<class Config> aConfig);
	~Lexer();

	LexedCode LexCode(ConstRef<StringData> aCode);
	LexedCode LexFile(ConstRef<String> aFilePath);

private:
	void ParseComment(Ref<LexingContext> aContext);
	void ParseStringLiteral(Ref<LexingContext> aContext);
	void ParseUnknownStatement(Ref<LexingContext> aContext);
	String ParseLexeme(Ref<LexingContext> aContext);
	void ParseCompilerDirective(Ref<LexingContext> aContext);
	void ParseNumberLiteral(Ref<LexingContext> context);

	ConstPtr<class Config> myConfig;
};
