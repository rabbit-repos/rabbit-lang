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

	ConstRef<VirtualList<Token>> GetLexemes() const;

	class LexemeListAccesser
	{
		friend class Interpreter;
		template <typename T>
		static void AddLexeme(RValue<T> aLexeme);
	};

private:
	VirtualList<Token> myLexemes;
};

template <typename T>
void CodeTokens::LexemeListAccesser::AddLexeme(RValue<T> aLexeme)
{
	myLexemes.Add(myLexemes);
}
