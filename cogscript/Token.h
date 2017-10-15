#pragma once
#include "TokenID.h"

class Token
{
public:
	Token(Const<TokenID> aTokenID, ConstRef<String> aTokenData);
	virtual ~Token();

	bool operator==(Const<TokenID> aRight) const;
	bool operator!=(Const<TokenID> aRight) const;

	TokenID GetTokenID() const;

private:
	String myTokenData;
	TokenID myTokenID;
};
