#include "MutableStringBlob.h"
#include <cstring>

MutableStringBlob::MutableStringBlob()
{
}

MutableStringBlob::MutableStringBlob(const Char * aString)
	: myData(wcslen(aString) + 1, false)
{
	memcpy(*myData, aString, (Length() + 1) * sizeof Char);
}

MutableStringBlob::MutableStringBlob(const size aExpectedLength)
	: myData(aExpectedLength + 1, false)
{
	*myData[0] = L'\0';
}

MutableStringBlob MutableStringBlob::FromASCII(const char * aString)
{
	i32 length = static_cast<i32>(strlen(aString));
	MutableStringBlob string;
	string.Resize(length);
	for (i32 i = 0; i < length; ++i)
		*string[i] = static_cast<Char>(aString[i]);
	return string;
}

void MutableStringBlob::Resize(const i32 aLength)
{
#ifdef _DEBUG
	if (aLength < 0)
		abort();
#endif
	myData.Resize(aLength);
}

i32 MutableStringBlob::Length() const
{
	return static_cast<i32>(myData.Length()) - 1;
}

Ptr<Char> MutableStringBlob::operator[](const i32 aIndex)
{
	return myData[aIndex];
}

ConstPtr<Char> MutableStringBlob::operator[](const i32 aIndex) const
{
	return myData[aIndex];
}

Ptr<Char> MutableStringBlob::operator*()
{
	return *myData;
}

ConstPtr<Char> MutableStringBlob::operator*() const
{
	return *myData;
}
