#include "pch.h"
#include "TranspilerContext.h"
#include "CodeTokens.h"
#include "VirtualList.h"

TranspilerContext::TranspilerContext(ConstRef<CodeTokens> aCodeTokens)
{
	myTokens = &aCodeTokens;
	myCursor = 0;
}

TranspilerContext::~TranspilerContext()
{
}

ConstRef<Token> TranspilerContext::At(Const<i32> aOffset /*=0*/) const
{
	return *myTokens->GetTokens()[myCursor + aOffset];
}

ConstRef<TokenContext> TranspilerContext::ContextAt(Const<i32> aOffset /*=0*/) const
{
	return At(aOffset).GetContext();
}

i32 TranspilerContext::GetCursorLocation() const
{
	return myCursor;
}

bool TranspilerContext::IsAtEnd() const
{
	return myCursor >= myTokens->GetTokens().Size();
}

Ref<SymbolMap> TranspilerContext::GetSymbolDatabase()
{
	return mySymbolDatabase;
}

ConstRef<SymbolMap> TranspilerContext::GetSymbolDatabase() const
{
	return mySymbolDatabase;
}
