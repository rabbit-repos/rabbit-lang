#include "String.h"
#include "MutableStringData.h"
#include "Types.h"

String::String()
{
	myData = null;
	myLength = 0;
}

String::String(ConstRef<MutableStringData> aString)
{
	myData = *aString;
	myLength = aString.Length();
}

String::String(const String & aString, const i32 aNumberOfCharacters)
{
	if (aNumberOfCharacters > aString.Length())
		abort();
	myData = aString.GetAddress();
}

String::String(ConstPtr<Char> aDataPoint, const i32 aLength)
{
	myData = aDataPoint;
	myLength = aLength;
}

String::~String()
{
}

i32 String::Length() const
{
	return myLength;
}

ConstPtr<Char> String::GetAddress() const
{
	return myData;
}

ConstRef<Char> String::operator[](const i32 aIndex) const
{
#ifdef _DEBUG
	if (aIndex < 0 || aIndex >= myLength)
		abort();
#endif
	return myData[aIndex];
}

String String::SubString(const i32 aStart, const i32 aLength)
{
#ifdef _DEBUG
	if (aStart < 0 || aStart + aLength > myLength)
		abort();
#endif
	return String(&myData[aStart], aLength);
}
