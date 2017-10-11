#pragma once
#include "Token.h"

class NotImplementedToken : public Token
{
public:
	NotImplementedToken(TokenID aTokenID, StringData aString);
	NotImplementedToken(TokenID aTokenID, ConstRef<String> aString);
	~NotImplementedToken();

	NotImplementedToken(RValue<NotImplementedToken> aOther);
	Ref<NotImplementedToken> operator=(RValue<NotImplementedToken> aOther);

	NotImplementedToken(ConstRef<NotImplementedToken> aOther);
	
	ConstRef<StringData> GetTokenString() const;

private:
	StringData myTokenString;
};

