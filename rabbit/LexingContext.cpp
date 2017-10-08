#include "pch.h"
#include "LexingContext.h"

LexingContext::LexingContext(ConstPtr<StringData> aCode)
{
	if (aCode == null)
		abort();

	myCode = aCode;
	myCursor = 0;
}

LexingContext::~LexingContext()
{
}

String LexingContext::Peek(Const<i32> aLength) const
{
	return String(*myCode).SubString(myCursor, Min(aLength, myCode->Size() - myCursor));
}

String LexingContext::StringAt(Const<i32> aOffset, Const<i32> aSize) const
{
	Const<i32> index = Clamp(myCursor + aOffset, 0, myCode->Size());
	return String(*myCode).SubString(myCursor, Min(aSize, myCode->Size() - myCursor));
}
