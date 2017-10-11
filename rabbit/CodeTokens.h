#pragma once
#include "VirtualList.h"
#include "Token.h"

class CodeTokens
{
public:
	CodeTokens();
	~CodeTokens();

	CodeTokens(RValue<CodeTokens> aMove);
	Ref<CodeTokens> operator=(RValue<CodeTokens> aMove);

	// Use Copy() instead
	CodeTokens(ConstRef<CodeTokens>) = delete;
	// Use Copy() instead
	Ref<CodeTokens> operator=(ConstRef<CodeTokens>) = delete;

	CodeTokens Copy() const;

	ConstRef<VirtualList<Token>> GetTokens() const;

	template <typename T>
	void AddToken(RValue<T> aLexeme);

private:
	VirtualList<Token> myLexemes;
};

template <typename T>
void CodeTokens::AddToken(RValue<T> aLexeme)
{
	myLexemes.Add<T>(std::move(aLexeme));
}
