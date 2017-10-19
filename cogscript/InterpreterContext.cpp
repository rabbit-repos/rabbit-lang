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

ConstRef<Token> InterpreterContext::At(Const<i32> aOffset /*=0*/) const
{
	return *myTokens->GetTokens()[myCursor + aOffset];
}

ConstRef<TokenContext> InterpreterContext::ContextAt(Const<i32> aOffset /*=0*/) const
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

Ref<SymbolMap> InterpreterContext::GetSymbolDatabase()
{
	return mySymbolDatabase;
}

ConstRef<SymbolMap> InterpreterContext::GetSymbolDatabase() const
{
	return mySymbolDatabase;
}
