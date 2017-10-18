#pragma once
#include "TokenID.h"
#include "TokenContext.h"

class Token
{
public:
	Token(Const<TokenID> aTokenID, ConstRef<TokenContext> aContext);
	Token(ConstRef<Token> aToken);
	virtual ~Token();

	Token(RValue<Token> aToken);
	Ref<Token> operator=(RValue<Token> aRight);

	bool operator==(Const<TokenID> aRight) const;
	bool operator!=(Const<TokenID> aRight) const;

	TokenID GetTokenID() const;
	ConstRef<TokenContext> GetContext() const;

	Token Copy() const;

	String ToString() const;

private:
	TokenContext myContext;
	TokenID myTokenID;
};
