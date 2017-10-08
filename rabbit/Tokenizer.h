#pragma once
#include "VirtualList.h"
#include "CodeTokens.h"

class TokenizerContext;

class Tokenizer
{
public:
	Tokenizer(ConstRef<class Config> aConfig);
	~Tokenizer();

	CodeTokens TokenizeCode(ConstRef<StringData> aCode);
	CodeTokens TokenizeFile(ConstRef<String> aFilePath);

private:
	void ParseComment(Ref<TokenizerContext> aContext);
	void ParseStringLiteral(Ref<TokenizerContext> aContext);
	void ParseUnknownStatement(Ref<TokenizerContext> aContext);
	String ParseLexeme(Ref<TokenizerContext> aContext);
	void ParseCompilerDirective(Ref<TokenizerContext> aContext);
	void ParseNumberLiteral(Ref<TokenizerContext> context);

	ConstPtr<class Config> myConfig;
};
