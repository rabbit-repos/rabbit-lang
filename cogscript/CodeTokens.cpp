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

CodeTokens::CodeTokens(RValue<Super> aMove)
	: Super(std::move(aMove))
{
}

Ref<CodeTokens> CodeTokens::operator=(RValue<CodeTokens> aMove)
{
	Super::operator=(std::move(aMove));
	return *this;
}

CodeTokens CodeTokens::Copy() const
{
	CodeTokens tokens(Super::Copy());
	return tokens;
}

ConstRef<VirtualList<Token>> CodeTokens::GetTokens() const
{
	return *this;
}

void CodeTokens::AddToken(Token aToken)
{
	if (aToken.GetTokenID() == TokenID::Invalid)
	{
		PrintLine(L"The Tokenizer may not generate tokens with TokenID set to TokenID::Invalid");
		FatalError();
	}

	Add(std::move(aToken));
}

CodeTokens::~CodeTokens()
{
}
