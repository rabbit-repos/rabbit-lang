#include "pch.h"
#include "TokenizerContext.h"

TokenizerContext::TokenizerContext(ConstPtr<StringData> aCode, Ref<CodeTokens> aTokens)
{
	if (aCode == null)
		FatalError();

	myCode = aCode;
	myTokens = &aTokens;
	myCursor = 0;
	myLineNumber = 0;
}

TokenizerContext::~TokenizerContext()
{
}

String TokenizerContext::Peek(Const<i32> aLength) const
{
	return String(*myCode).SubString(myCursor, Min(aLength, myCode->Size() - myCursor));
}

String TokenizerContext::StringAt(Const<i32> aOffset, Const<i32> aSize) const
{
	return String(*myCode).SubString(Max<i32>(0, myCursor + aOffset), Min(aSize, myCode->Size() - myCursor));
}
