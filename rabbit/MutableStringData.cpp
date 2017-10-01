#include "MutableStringData.h"
#include <cstring>

MutableStringData::MutableStringData()
{
}

MutableStringData::MutableStringData(const Char * aString)
	: myData(wcslen(aString) + 1, false)
{
	memcpy(*myData, aString, (Length() + 1) * sizeof Char);
}

MutableStringData::MutableStringData(const size aExpectedLength)
	: myData(aExpectedLength + 1, false)
{
	*myData[0] = L'\0';
}

MutableStringData MutableStringData::FromASCII(const char * aString)
{
	i32 length = static_cast<i32>(strlen(aString));
	MutableStringData string;
	string.Resize(length);
	for (i32 i = 0; i < length; ++i)
		*string[i] = static_cast<Char>(aString[i]);
	return string;
}

void MutableStringData::Resize(const i32 aLength)
{
#ifdef _DEBUG
	if (aLength < 0)
		abort();
#endif
	myData.Resize(aLength);
}

i32 MutableStringData::Length() const
{
	return static_cast<i32>(myData.Length()) - 1;
}

Ptr<Char> MutableStringData::operator[](const i32 aIndex)
{
	return myData[aIndex];
}

ConstPtr<Char> MutableStringData::operator[](const i32 aIndex) const
{
	return myData[aIndex];
}

Ptr<Char> MutableStringData::operator*()
{
	return *myData;
}

ConstPtr<Char> MutableStringData::operator*() const
{
	return *myData;
}
