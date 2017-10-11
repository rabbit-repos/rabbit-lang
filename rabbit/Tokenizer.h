#pragma once
#include "VirtualList.h"
#include "CodeTokens.h"
#include "TokenID.h"

class TokenizerContext;
class Stopwatch;

class Tokenizer
{
public:
	Tokenizer(ConstRef<class Config> aConfig);
	~Tokenizer();

	CodeTokens TokenizeCode(ConstRef<StringData> aCode);
	CodeTokens TokenizeFile(ConstRef<String> aFilePath, Ptr<Stopwatch> aWatchToRestartWhenFileIsRead = null);
	
private:
	TokenID TryReadSpecialToken(Ref<TokenizerContext> aContext);
	void ParseComment(Ref<TokenizerContext> aContext);
	void ParseStringLiteral(Ref<TokenizerContext> aContext);
	void ParseUnknownStatement(Ref<TokenizerContext> aContext);
	String ParseToken(Ref<TokenizerContext> aContext);
	void ParseCompilerDirective(Ref<TokenizerContext> aContext);
	void ParseNumberLiteral(Ref<TokenizerContext> context);

	ConstPtr<class Config> myConfig;
};
