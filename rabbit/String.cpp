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
	mySize = 0;
}

String::String(ConstRef<StringData> aString)
	: String()
{
	myData = aString.GetAddress();
	mySize = aString.Size();

#ifdef _DEBUG
	myOwner = &aString;
	++aString.myNumReferences;
#endif
}

String::String(ConstRef<String> aString, Const<i32> aNumberOfCharacters)
	: String()
{
	if (aNumberOfCharacters > aString.Size())
		abort();
	myData = aString.GetAddress();
}

String::String(ConstPtr<StringData> aOwner, ConstPtr<Char> aDataPoint, Const<i32> aSize)
	: String()
{
#ifdef _DEBUG
	myOwner = aOwner;
	if (myOwner)
		++myOwner->myNumReferences;
#else
	(aOwner);
#endif

	if (aSize > 0)
	{
		myData = aDataPoint;
		mySize = aSize;
	}
	else
	{
		myData = null;
		mySize = 0;
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
		mySize = static_cast<i32>(wcslen(aString));
	}
	else
	{
		myData = null;
		mySize = 0;
	}
}

String String::MakeView(Const<i32> aStart, Const<i32> aLength) const
{
#ifdef _DEBUG
	return String(myOwner, &myData[aStart], aLength);
#else
	return String(null, &myData[aStart], aLength);
#endif
}

String String::ChopLeft(Const<i32> aEnd) const
{
#ifdef _DEBUG
	if (aEnd < 0 || aEnd > mySize)
		abort();
#endif
	return MakeView(0, aEnd);
}

String String::ChopRight(Const<i32> aBegin) const
{
#ifdef _DEBUG
	if (aBegin < 0 || aBegin > mySize)
		abort();
#endif
	return MakeView(aBegin, mySize - aBegin);
}

bool String::FindFirst(Const<Char> aChar, Out<i32> aIndex, Const<i32> aBeginAt /*= 0*/) const
{
	Const<i32> n = Size();
	for (i32 i = aBeginAt; i < n; ++i)
	{
		if ((*this)[i] == aChar)
		{
			aIndex = i;
			return true;
		}
	}
	return false;
}

bool String::FindLast(Const<Char> aChar, Out<i32> aIndex, Const<i32> aBeginAt /*= MaxOf<i32>*/) const
{
	for (i32 i = Min(Size() - 1, aBeginAt); i >= 0; --i)
	{
		if ((*this)[i] == aChar)
		{
			aIndex = i;
			return true;
		}
	}
	return false;
}

bool String::CopyTo(Ptr<Char> aData, Const<i32> aLength) const
{
	if (mySize + 1 >= aLength)
		return false;

	memcpy(aData, myData, mySize * sizeof Char);
	aData[mySize] = L'\0';
	return true;
}

String::~String()
{
#ifdef _DEBUG
	if (myOwner)
		--myOwner->myNumReferences;

	myData = null;
	myOwner = null;
	mySize = -1;
#endif
}

i32 String::Size() const
{
	return mySize;
}

bool String::IsEmpty() const
{
	return mySize == 0;
}

ConstPtr<Char> String::GetAddress() const
{
	return myData;
}

std::string String::ToASCII() const
{
	std::string str;
	if (Size() > 0)
	{
		Const<i32> n = Size();
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
	if (Size() > 0)
	{
		str.resize(Size());
		memcpy(&str[0], GetAddress(), sizeof Char * Size());
	}
	return str;
}

ConstRef<Char> String::operator[](Const<i32> aIndex) const
{
#ifdef _DEBUG
	if (aIndex < 0 || aIndex >= mySize)
		abort();
#endif
	return myData[aIndex];
}

String String::SubString(Const<i32> aStart, Const<i32> aLength) const
{
#ifdef _DEBUG
	if (aStart < 0 || aStart + aLength > mySize)
		abort();
#endif

	return MakeView(aStart, aLength);
}

String String::Trim() const
{
	if (!mySize)
		return String();

	i32 start = 0;
	while (start < mySize && CharUtility::IsWhiteSpace(myData[start]))
		++start;
	i32 end = mySize - 1;
	while (end > 0 && CharUtility::IsWhiteSpace(myData[end]))
		--end;

	return MakeView(start, end - start + 1);
}

bool String::BeginsWith(ConstRef<String> aString) const
{
	if (aString.Size() > mySize)
		return false;
	for (i32 i = 0; i < aString.Size(); ++i)
		if ((*this)[i] != aString[i])
			return false;
	return true;
}

bool String::EndsWith(ConstRef<String> aString) const
{
	if (aString.Size() > mySize)
		return false;
	Const<i32> start = mySize - aString.Size();
	for (i32 i = 0; i < aString.Size(); ++i)
		if ((*this)[start + i] != aString[i])
			return false;
	return true;
}

bool String::Equals(ConstRef<String> aOther) const
{
	return *this == aOther;
}

bool String::EqualsIgnoreCase(ConstRef<String> aOther) const
{
	if (Size() != aOther.Size())
		return false;
	for (i32 i = 0, n = Size(); i < n; ++i)
		if (myData[i] != aOther[i] && CharUtility::ToLower(myData[i]) != CharUtility::ToLower(aOther[i]))
			return false;
	return true;
}

bool String::operator==(ConstPtr<char> aOther) const
{
	Const<i32> length = static_cast<i32>(strlen(aOther));
	if (length != Size())
		return false;
	for (i32 i = 0; i < length; ++i)
		if (static_cast<Char>(aOther[i]) != myData[i])
			return false;
	return true;
}

bool String::operator!=(ConstPtr<char> aOther) const
{
	return !(*this == aOther);
}

bool String::operator==(ConstPtr<wchar_t> aOther) const
{
	return wcscmp(static_cast<ConstPtr<Char>>(aOther), myData) == 0;
}

bool String::operator!=(ConstPtr<wchar_t> aOther) const
{
	return !(*this == aOther);
}

bool String::operator==(ConstRef<String> aOther) const
{
	if (Size() != aOther.Size())
		return false;
	return memcmp(GetAddress(), aOther.GetAddress(), Size() * sizeof Char) == 0;
}

bool String::operator!=(ConstRef<String> aOther) const
{
	return !(*this == aOther);
}

Ref<std::wostream> operator<<(Ref<std::wostream> aOut, ConstRef<String> aString)
{
	aOut.write(aString.GetAddress(), aString.Size());
	return aOut;
}

Ref<std::ostream> operator<<(Ref<std::ostream> aOut, ConstRef<String> aString)
{
	for (i32 i=0; i<aString.Size(); ++i)
		aOut.write(reinterpret_cast<ConstPtr<char>>(&aString[i]), 1);
	return aOut;
}

void String::Clear()
{
	*this = String();
}
