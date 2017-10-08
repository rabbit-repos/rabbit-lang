#include "pch.h"
#include "TokenizerContext.h"

TokenizerContext::TokenizerContext(ConstPtr<StringData> aCode)
{
	if (aCode == null)
		abort();

	myCode = aCode;
	myCursor = 0;
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
	Const<i32> index = Clamp(myCursor + aOffset, 0, myCode->Size());
	return String(*myCode).SubString(myCursor, Min(aSize, myCode->Size() - myCursor));
}
