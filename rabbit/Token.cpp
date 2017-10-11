#include "pch.h"
#include "Token.h"

Token::Token(Const<TokenID> aTokenID)
{
	myTokenID = aTokenID;
}

Token::~Token()
{
}

TokenID Token::GetTokenID() const
{
	return myTokenID;
}

bool Token::operator==(Const<TokenID> aRight) const
{
	return myTokenID == aRight;
}

bool Token::operator!=(Const<TokenID> aRight) const
{
	return myTokenID != aRight;
}
