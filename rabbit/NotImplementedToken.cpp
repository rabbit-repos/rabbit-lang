#include "pch.h"
#include "NotImplementedToken.h"

NotImplementedToken::NotImplementedToken(TokenID aTokenID, StringData aString)
	: Token(aTokenID)
{
	myTokenString = std::move(aString);
}

NotImplementedToken::NotImplementedToken(TokenID aTokenID, ConstRef<String> aString)
	: NotImplementedToken(aTokenID, StringData(aString))
{
}

NotImplementedToken::NotImplementedToken(ConstRef<NotImplementedToken> aOther) : Token(aOther.GetTokenID())
{
	myTokenString = aOther.myTokenString.Copy();
}

NotImplementedToken::NotImplementedToken(RValue<NotImplementedToken> aOther) : NotImplementedToken(aOther.GetTokenID(), aOther.GetTokenString().Copy())
{
	*this = std::move(aOther);
}

Ref<NotImplementedToken> NotImplementedToken::operator=(RValue<NotImplementedToken> aOther)
{
	myTokenString = std::move(aOther.myTokenString);
	return *this;
}

NotImplementedToken::~NotImplementedToken()
{
}

ConstRef<StringData> NotImplementedToken::GetTokenString() const
{
	return myTokenString;
}
