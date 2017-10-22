#pragma once
#include "Namespace.h"
#include "ErrorCode.h"

enum class KeywordID : u8;
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
	
	KeywordID KeywordAt(Const<i32> aOffset = 0) const;

	Ref<TokenContext> ContextAt(Const<i32> aOffset = 0);
	ConstRef<TokenContext> ContextAt(Const<i32> aOffset = 0) const;

	void AdvanceCursor();
	void AdvanceCursor(Const<i32> aAmount);

	i32 GetCursorLocation() const;
	bool IsAtEnd(Const<i32> aOffset = 0) const;

	Ref<Namespace> GetGlobalNamespace();
	ConstRef<Namespace> GetGlobalNamespace() const;

	void ReportErrorWithDefaultMessage(Const<ErrorCode::Type> aError, Const<i32> aOffset);
	void ReportError(Const<ErrorCode::Type> aError, ConstRef<String> aErrorDescription, Const<i32> aOffset);
	
private:
	Namespace myGlobalNamepsace;
	ConstPtr<CodeTokens> myTokens;
	i32 myCursor;
};
