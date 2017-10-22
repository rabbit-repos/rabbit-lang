#pragma once
#include "Namespace.h"
#include "ErrorCode.h"

class CodeTokens;
class Token;
class TokenContext;

class InterpreterContext
{
public:
	InterpreterContext(ConstRef<CodeTokens> aCodeTokens);
	~InterpreterContext();

	Ref<Token> At(Const<i32> aOffset = 0);
	ConstRef<Token> At(Const<i32> aOffset = 0) const;
	
	Ref<TokenContext> ContextAt(Const<i32> aOffset = 0);
	ConstRef<TokenContext> ContextAt(Const<i32> aOffset = 0) const;

	i32 GetCursorLocation() const;
	bool IsAtEnd() const;

	Ref<Namespace> GetDefaultNamespace();
	ConstRef<Namespace> GetDefaultNamespace() const;

	void ReportErrorWithDefaultMessage(Const<ErrorCode::Type> aError, Const<i32> aOffset);
	void ReportError(Const<ErrorCode::Type> aError, ConstRef<String> aErrorDescription, Const<i32> aOffset);
	
private:
	Namespace mySymbolDatabase;
	ConstPtr<CodeTokens> myTokens;
	i32 myCursor;
};