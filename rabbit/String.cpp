#include "String.h"
#include "StringData.h"
#include "Types.h"
#include <cstring>

String::String()
{
	myData = null;
	myOwner = null;
	myLength = 0;
}

String::String(ConstRef<StringData> aString)
{
	myData = *aString;
	myLength = aString.Length();

#ifdef _DEBUG
	myOwner = &aString;
	++aString.myNumReferences;
#endif
}

String::String(const String & aString, const i32 aNumberOfCharacters)
{
	if (aNumberOfCharacters > aString.Length())
		abort();
	myData = aString.GetAddress();
}

String::String(ConstPtr<StringData> aOwner, ConstPtr<Char> aDataPoint, const i32 aLength)
{
	myOwner = aOwner;
	myData = aDataPoint;
	myLength = aLength;
}

String::~String()
{
#ifdef _DEBUG
	if (myOwner)
		--myOwner->myNumReferences;

	myData = null;
	myOwner = null;
	myLength = -1;
#endif
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
	return String(myOwner, &myData[aStart], aLength);
}

bool String::operator==(const char * aOther) const
{
	i32 length = static_cast<i32>(strlen(aOther));
	if (length != Length())
		return false;
	for (i32 i = 0; i < length; ++i)
		if (static_cast<Char>(aOther[i]) != myData[i])
			return false;
	return true;
}

bool String::operator!=(const char * aOther) const
{
	return !(*this == aOther);
}

bool String::operator==(const wchar_t * aOther) const
{
	return wcscmp((const Char*)(aOther), myData) == 0;
}

bool String::operator!=(const wchar_t * aOther) const
{
	return !(*this == aOther);
}

bool String::operator==(const String & aOther) const
{
	if (Length() != aOther.Length())
		return false;
	return memcmp(GetAddress(), aOther.GetAddress(), Length() * sizeof Char) == 0;
}

bool String::operator!=(const String & aOther) const
{
	return !(*this == aOther);
}
