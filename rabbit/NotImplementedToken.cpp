#include "pch.h"
#include "NotImplementedToken.h"

NotImplementedToken::NotImplementedToken(TokenID aTokenID, String aString)
	: Token(aTokenID)
{
	myTokenString = std::move(aString);
}

NotImplementedToken::~NotImplementedToken()
{
}
