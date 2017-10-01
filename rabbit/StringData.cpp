#include "pch.h"
#include "StringData.h"
#include "String.h"

StringData::StringData()
{
#ifdef _DEBUG
	myNumReferences = 0;
#endif
}

StringData::StringData(ConstPtr<Char> aString)
	: myData(static_cast<i32>(wcslen(aString) + 1), false)
{
	memcpy(myData.GetAddress(), aString, (Length() + 1) * sizeof Char);
#ifdef _DEBUG
	myNumReferences = 0;
#endif
}

StringData::StringData(Const<i32> aExpectedLength)
	: myData(aExpectedLength + 1, false)
{
	myData[0] = L'\0';
#ifdef _DEBUG
	myNumReferences = 0;
#endif
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

StringData::StringData(ConstPtr<Char> aString, Const<i32> aLength)
	: myData(aLength + 1, false)
{
	myData.Resize(aLength + 1, false);
	memcpy(myData.GetAddress(), aString, aLength * sizeof Char);
	myData[aLength] = L'\0';
#ifdef _DEBUG
	myNumReferences = 0;
#endif
}

StringData::StringData(ConstRef<String> aString)
	: myData(aString.Length() + 1, false)
{
	myData.Resize(aString.Length() + 1, false);
	memcpy(myData.GetAddress(), aString.GetAddress(), Length() * sizeof Char);
	myData[Length()] = L'\0';
#ifdef _DEBUG
	myNumReferences = 0;
#endif
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
#ifdef _DEBUG
	myNumReferences = 0;
#endif
	return *this;
}

StringData StringData::FromASCII(ConstPtr<char> aString)
{
	i32 length = static_cast<i32>(strlen(aString));
	StringData string;
	string.Resize(length);
	for (i32 i = 0; i < length; ++i)
		string[i] = static_cast<Char>(aString[i]);
	return string;
}

void StringData::Resize(Const<i32> aLength)
{
#ifdef _DEBUG
	if (aLength < 0)
		abort();
#endif
	myData.Resize(aLength + 1);
}

void StringData::Reserve(Const<i32> aLength)
{
#ifdef _DEBUG
	if (aLength < 0)
		abort();
#endif
	myData.Reserve(aLength + 1);
}

i32 StringData::Length() const
{
	// PERF: Maybe move to own variable?
	return static_cast<i32>(myData.Length()) - 1;
}

i32 StringData::Capacity() const
{
	// PERF: Maybe move to own variable?
	return static_cast<i32>(myData.Capacity()) - 1;
}

Ref<Char> StringData::operator[](Const<i32> aIndex)
{
	return myData[aIndex];
}

ConstRef<Char> StringData::operator[](Const<i32> aIndex) const
{
	return myData[aIndex];
}

Ref<Char> StringData::operator*()
{
	return *myData.GetAddress();
}

ConstRef<Char> StringData::operator*() const
{
	return *myData.GetAddress();
}

Ptr<Char> StringData::GetAddress()
{
	return myData.GetAddress();
}

ConstPtr<Char> StringData::GetAddress() const
{
	return myData.GetAddress();
}

void StringData::Append(ConstPtr<wchar_t> aString, Const<i32> aLength)
{
	CheckForReferences();

	while (Length() + aLength > Capacity())
		Reserve(Capacity() * 2);

	memcpy(&myData[Length()], aString, aLength);
	myData.SetLength(Length() + aLength);
}

void StringData::Append(ConstPtr<wchar_t> aString)
{
	Append(aString, static_cast<i32>(wcslen(aString)));
}

void StringData::CheckForReferences() const
{
#ifdef _DEBUG
	if (myNumReferences > 0)
	{
		std::cout << "This operation is not allowed while there are references to this data!" << std::endl;
		abort();
	}
#endif
}

std::wostream & operator<<(Ref<std::wostream> aOut, ConstRef<StringData> aString)
{
	aOut << *aString;
	return aOut;
}

std::ostream & operator<<(Ref<std::ostream> aOut, ConstRef<StringData> aString)
{
	for (i32 i = 0; i < aString.Length(); ++i)
		aOut.write(reinterpret_cast<ConstPtr<char>>(&aString[i]), 1);
	return aOut;
}

void from_json(ConstRef<json> aNode, Ref<StringData> aString)
{
	aString = StringData::FromASCII(aNode.get<std::string>().data());
}

void to_json(Ref<json> aNode, ConstRef<StringData> aString)
{
	aNode = *aString;
}
