
#pragma once
#include "VirtualList.h"
#include "Token.h"

class CodeTokens
{
public:
	CodeTokens();
	~CodeTokens();
	
	// Use Copy instead
	CodeTokens(ConstRef<CodeTokens>) = delete;
	// Use Copy instead
	Ref<CodeTokens> operator=(ConstRef<CodeTokens>) = delete;
	
	CodeTokens(RValue<CodeTokens> aMove);
	Ref<CodeTokens> operator=(RValue<CodeTokens> aMove);

	CodeTokens Copy() const;

	ConstRef<VirtualList<Token>> GetTokens() const;

	void AddToken(Token aToken);

private:
	VirtualList<Token> myTokens;
};
