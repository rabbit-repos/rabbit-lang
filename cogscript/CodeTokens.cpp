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
	myTokens = std::move(aMove.myTokens);
	return *this;
}

CodeTokens CodeTokens::Copy() const
{
	CodeTokens copy;
	copy.myTokens = myTokens.Copy();
	return copy;
}

ConstRef<VirtualList<Token>> CodeTokens::GetTokens() const
{
	return myTokens;
}

void CodeTokens::AddToken(Token aToken)
{
	myTokens.Add(std::move(aToken));
}

CodeTokens::~CodeTokens()
{
}
