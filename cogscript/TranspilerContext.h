#pragma once
#include "SymbolMap.h"

class CodeTokens;
class Token;
class TokenContext;

class TranspilerContext
{
public:
	TranspilerContext(ConstRef<CodeTokens> aCodeTokens);
	~TranspilerContext();

	ConstRef<Token> At(Const<i32> aOffset = 0) const;
	ConstRef<TokenContext> ContextAt(Const<i32> aOffset = 0) const;

	i32 GetCursorLocation() const;
	bool IsAtEnd() const;

	Ref<SymbolMap> GetSymbolDatabase();
	ConstRef<SymbolMap> GetSymbolDatabase() const;

private:
	SymbolMap mySymbolDatabase;
	ConstPtr<CodeTokens> myTokens;
	i32 myCursor;
};
