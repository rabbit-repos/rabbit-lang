#include "pch.h"
#include "Token.h"

Token::Token(Const<TokenID> aTokenID, ConstRef<TokenContext> aContext)
{
	myTokenID = aTokenID;
	myContext = aContext; 
}

Token::Token(RValue<Token> aToken)
{
	*this = std::move(aToken);
}

Token::Token(ConstRef<Token> aToken)
{
	myTokenID = aToken.myTokenID;
	myContext = aToken.GetContext();
}

Token::~Token()
{
}

Ref<Token> Token::operator=(RValue<Token> aToken)
{
	myTokenID = std::move(aToken.myTokenID);
	myContext = std::move(aToken.myContext);
	return *this;
}

TokenID Token::GetTokenID() const
{
	return myTokenID;
}

ConstRef<TokenContext> Token::GetContext() const
{
	return myContext;
}

Token Token::Copy() const
{
	return Token(myTokenID, myContext);
}

bool Token::operator==(Const<TokenID> aRight) const
{
	return myTokenID == aRight;
}

bool Token::operator!=(Const<TokenID> aRight) const
{
	return myTokenID != aRight;
}
