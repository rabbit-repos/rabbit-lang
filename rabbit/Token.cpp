#include "pch.h"
#include "Token.h"

Token::Token(Const<TokenID> aTokenID)
{
	myTokenID = aTokenID;
}

Token::~Token()
{
}

bool Token::operator==(Const<TokenID> aRight) const
{
	return myTokenID == aRight;
}

bool Token::operator!=(Const<TokenID> aRight) const
{
	return myTokenID != aRight;
}
