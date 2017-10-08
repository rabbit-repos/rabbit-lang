#include "pch.h"
#include "CodeTokens.h"

CodeTokens::CodeTokens()
{
}

CodeTokens::CodeTokens(RValue<CodeTokens> aMove)
	: CodeTokens()
{
	*this = std::move(aMove);
}

Ref<CodeTokens> CodeTokens::operator=(RValue<CodeTokens> aMove)
{
	myLexemes = std::move(aMove.myLexemes);
	return *this;
}

CodeTokens CodeTokens::Copy() const
{
	CodeTokens copy;
	copy.myLexemes = myLexemes.Copy();
	return copy;
}

ConstRef<VirtualList<Token>> CodeTokens::GetLexemes() const
{
	return myLexemes;
}

CodeTokens::~CodeTokens()
{
}
