#pragma once

#include "VirtualList.h"
#include "Token.h"

class CodeTokens final : private VirtualList<Token>
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
	using Super = VirtualList<Token>;
	CodeTokens(RValue<Super> aMove);
};
