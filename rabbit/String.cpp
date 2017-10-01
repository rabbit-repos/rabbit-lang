#include "pch.h"
#include "String.h"
#include "StringData.h"
#include "CharUtility.h"

String::String()
{
	myData = null;
#ifdef _DEBUG
	myOwner = null;
#endif
	myLength = 0;
}

String::String(ConstRef<StringData> aString)
	: String()
{
	myData = aString.GetAddress();
	myLength = aString.Length();

#ifdef _DEBUG
	myOwner = &aString;
	++aString.myNumReferences;
#endif
}

String::String(const String & aString, const i32 aNumberOfCharacters)
	: String()
{
	if (aNumberOfCharacters > aString.Length())
		abort();
	myData = aString.GetAddress();
}

String::String(ConstPtr<StringData> aOwner, ConstPtr<Char> aDataPoint, const i32 aLength)
	: String()
{
#ifdef _DEBUG
	myOwner = aOwner;
	if (myOwner)
		++myOwner->myNumReferences;
#else
	(aOwner);
#endif

	if (aLength > 0)
	{
		myData = aDataPoint;
		myLength = aLength;
	}
	else
	{
		myData = null;
		myLength = 0;
	}
}

String::String(ConstPtr<Char> aString)
{
#ifdef _DEBUG
	myOwner = null;
#endif
	
	if (aString)
	{
		myData = aString;
		myLength = static_cast<i32>(wcslen(aString));
	}
	else
	{
		myData = null;
		myLength = 0;
	}
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

std::string String::ToASCII() const
{
	std::string str;
	if (Length() > 0)
	{
		Const<i32> n = Length();
		str.resize(n);
		
		for (i32 i=0; i<n; ++i)
		{
			str[i] = static_cast<char>((*this)[i]);
		}
	}
	return str;
}

std::wstring String::ToWideString() const
{
	std::wstring str;
	if (Length() > 0)
	{
		str.resize(Length());
		memcpy(&str[0], GetAddress(), sizeof Char * Length());
	}
	return str;
}

ConstRef<Char> String::operator[](const i32 aIndex) const
{
#ifdef _DEBUG
	if (aIndex < 0 || aIndex >= myLength)
		abort();
#endif
	return myData[aIndex];
}

String String::SubString(const i32 aStart, const i32 aLength) const
{
#ifdef _DEBUG
	if (aStart < 0 || aStart + aLength > myLength)
		abort();
#endif

#ifdef _DEBUG
	return String(myOwner, &myData[aStart], aLength);
#else
	return String(null, &myData[aStart], aLength);
#endif
}

String String::Trim() const
{
	if (!myLength)
		return String();

	i32 start = 0;
	while (start < myLength && CharUtility::IsWhiteSpace(myData[start]))
		++start;
	i32 end = myLength - 1;
	while (end > 0 && CharUtility::IsWhiteSpace(myData[end]))
		--end;
#ifdef _DEBUG
	return String(myOwner, &myData[start], end - start + 1);
#else
	return String(null, &myData[start], end - start + 1);
#endif
}

bool String::BeginsWith(ConstRef<String> aString) const
{
	if (aString.Length() > myLength)
		return false;
	for (i32 i = 0; i < aString.Length(); ++i)
		if ((*this)[i] != aString[i])
			return false;
	return true;
}

bool String::EndsWith(ConstRef<String> aString) const
{
	if (aString.Length() > myLength)
		return false;
	Const<i32> start = myLength - aString.Length();
	for (i32 i = 0; i < aString.Length(); ++i)
		if ((*this)[start + i] != aString[i])
			return false;
	return true;
}

bool String::operator==(const char * aOther) const
{
	Const<i32> length = static_cast<i32>(strlen(aOther));
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
	return wcscmp(static_cast<ConstPtr<Char>>(aOther), myData) == 0;
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

Ref<std::wostream> operator<<(Ref<std::wostream> aOut, ConstRef<String> aString)
{
	aOut.write(aString.GetAddress(), aString.Length());
	return aOut;
}

Ref<std::ostream> operator<<(Ref<std::ostream> aOut, ConstRef<String> aString)
{
	for (i32 i=0; i<aString.Length(); ++i)
		aOut.write(reinterpret_cast<ConstPtr<char>>(&aString[i]), 1);
	return aOut;
}
