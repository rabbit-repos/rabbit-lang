#pragma once
#include "Token.h"

class NotImplementedToken : public Token
{
public:
	NotImplementedToken(TokenID aTokenID, String aString);
	~NotImplementedToken();

private:
	String myTokenString;
};

