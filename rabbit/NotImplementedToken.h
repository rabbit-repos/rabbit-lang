#pragma once
#include "Token.h"

class NotImplementedToken : public Token
{
public:
	NotImplementedToken(Const<TokenID> aToken, String aString);
	~NotImplementedToken();
};

