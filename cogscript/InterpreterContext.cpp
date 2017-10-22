#include "pch.h"
#include "InterpreterContext.h"
#include "CodeTokens.h"
#include "VirtualList.h"

InterpreterContext::InterpreterContext(ConstRef<CodeTokens> aCodeTokens)
{
	myTokens = &aCodeTokens;
	myCursor = 0;
}

InterpreterContext::~InterpreterContext()
{
}

Ref<Token> InterpreterContext::At(Const<i32> aOffset /*= 0*/)
{
	return *myTokens->GetTokens()[Clamp(myCursor + aOffset, 0, myTokens->GetTokens().Size() - 1)];
}

ConstRef<Token> InterpreterContext::At(Const<i32> aOffset /*=0*/) const
{
	return *myTokens->GetTokens()[Clamp(myCursor + aOffset, 0, myTokens->GetTokens().Size() - 1)];
}

ConstRef<TokenContext> InterpreterContext::ContextAt(Const<i32> aOffset /*=0*/) const
{
	return At(aOffset).GetContext();
}
Ref<TokenContext> InterpreterContext::ContextAt(Const<i32> aOffset /*= 0*/)
{
	return At(aOffset).GetContext();
}

i32 InterpreterContext::GetCursorLocation() const
{
	return myCursor;
}

bool InterpreterContext::IsAtEnd() const
{
	return myCursor >= myTokens->GetTokens().Size();
}

Ref<Namespace> InterpreterContext::GetDefaultNamespace()
{
	return mySymbolDatabase;
}

ConstRef<Namespace> InterpreterContext::GetDefaultNamespace() const
{
	return mySymbolDatabase;
}

void InterpreterContext::ReportErrorWithDefaultMessage(Const<ErrorCode::Type> aError, Const<i32> aOffset)
{
	At(aOffset).AddError(aError, ErrorCode::GetDefaultMessage(aError));
}

void InterpreterContext::ReportError(Const<ErrorCode::Type> aError, ConstRef<String> aErrorDescription, Const<i32> aOffset)
{
	At(aOffset).AddError(aError, aErrorDescription);
}
