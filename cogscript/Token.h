#pragma once
#include "TokenID.h"
#include "TokenContext.h"
#include "List.h"
#include "ErrorCode.h"

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

	Ref<TokenContext> GetContext();
	ConstRef<TokenContext> GetContext() const;

	ConstRef<String> GetContextData() const;

	Token Copy() const;

	String TypeToString() const;

	void AddError(Const<ErrorCode::Type> aErrorCode, ConstRef<String> aErrorMessage);

private:
	List<StringData> myErrorList;
	TokenContext myContext;
	TokenID myTokenID;
};
