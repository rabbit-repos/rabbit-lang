#pragma once
#include "TokenID.h"

class Token
{
public:
	Token(Const<TokenID> aTokenID);
	virtual ~Token();

	bool operator==(Const<TokenID> aRight) const;
	bool operator!=(Const<TokenID> aRight) const;

	TokenID GetTokenID() const;

private:
	TokenID myTokenID;
};
