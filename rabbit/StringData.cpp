#include "StringData.h"
#include <cstring>
#include <iostream>

StringData::StringData()
{
	myNumReferences = 0;
}

StringData::StringData(ConstPtr<Char> aString)
	: myData(wcslen(aString) + 1, false)
{
	memcpy(&*myData, aString, (Length() + 1) * sizeof Char);
	myNumReferences = 0;
}

StringData::StringData(const size aExpectedLength)
	: myData(aExpectedLength + 1, false)
{
	myData[0] = L'\0';
	myNumReferences = 0;
}

StringData::StringData(RValue<StringData> aOther)
	: StringData()
{
	*this = std::move(aOther);
}

StringData::StringData(ConstRef<StringData> aOther)
	: StringData()
{
	*this = aOther;
}

StringData::~StringData()
{
#ifdef _DEBUG
	if (myNumReferences > 0)
	{
		std::cout << "There are still references remaining!" << std::endl;
		abort();
	}
#endif
}

Ref<StringData> StringData::operator=(RValue<StringData> aOther)
{
#ifdef _DEBUG
	if (aOther.myNumReferences > 0)
	{
		std::cout << "There are still references remaining!" << std::endl;
		abort();
	}

	myNumReferences = 0;
#endif

	myData = std::move(aOther.myData);

	return *this;
}

Ref<StringData> StringData::operator=(ConstRef<StringData> aOther)
{
	myData = aOther.myData;
	myNumReferences = 0;
	return *this;
}

StringData StringData::FromASCII(const char * aString)
{
	i32 length = static_cast<i32>(strlen(aString));
	StringData string;
	string.Resize(length);
	for (i32 i = 0; i < length; ++i)
		string[i] = static_cast<Char>(aString[i]);
	return string;
}

void StringData::Resize(const i32 aLength)
{
#ifdef _DEBUG
	if (aLength < 0)
		abort();
#endif
	myData.Resize(aLength);
}

i32 StringData::Length() const
{
	return static_cast<i32>(myData.Length()) - 1;
}

Ref<Char> StringData::operator[](const i32 aIndex)
{
	return myData[aIndex];
}

ConstRef<Char> StringData::operator[](const i32 aIndex) const
{
	return myData[aIndex];
}

Ref<Char> StringData::operator*()
{
	return *myData;
}

ConstRef<Char> StringData::operator*() const
{
	return *myData;
}
