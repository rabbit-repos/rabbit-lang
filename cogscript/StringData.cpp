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
{
	myData.Resize(static_cast<i32>(wcslen(aString) + 1));
	memcpy(myData.GetAddress(), aString, (Size() + 1) * sizeof Char);
#ifdef _DEBUG
	myNumReferences = 0;
#endif
}

StringData::StringData(ConstRef<std::wstring> aString)
	: StringData(aString.data(), static_cast<i32>(aString.length()))
{
}

StringData::StringData(Const<i32> aExpectedLength)
	: myData(aExpectedLength + 1)
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

StringData::StringData(ConstPtr<Char> aString, Const<i32> aLength)
	: myData(aLength + 1)
{
	myData.Resize(aLength + 1);
	memcpy(myData.GetAddress(), aString, aLength * sizeof Char);
	myData[aLength] = L'\0';
#ifdef _DEBUG
	myNumReferences = 0;
#endif
}

StringData::StringData(ConstRef<String> aString)
	: myData(aString.Size() + 1)
{
	myData.Resize(aString.Size() + 1);
	memcpy(myData.GetAddress(), aString.GetAddress(), Size() * sizeof Char);
	myData[Size()] = L'\0';
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

StringData StringData::Copy() const
{
	StringData data;
	data.myData = myData.Copy();
#ifdef _DEBUG
	data.myNumReferences = 0;
#endif
	return data;
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
	myData[Size()] = L'\0';
}

bool StringData::Reserve(Const<i32> aLength)
{
#ifdef _DEBUG
	if (aLength < 0)
		abort();
#endif
	return myData.Reserve(aLength + 1);
}

i32 StringData::Size() const
{
	// PERF: Maybe move to own variable?
	return Max(0, static_cast<i32>(myData.Size()) - 1);
}

i32 StringData::Capacity() const
{
	// PERF: Maybe move to own variable?
	return Max(0, static_cast<i32>(myData.Capacity()) - 1);
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

void StringData::Append(ConstPtr<Char> aString, Const<i32> aLength)
{
	CheckForReferences();
	MakeSizeFor(aLength);

	memcpy(&myData[Size()], aString, sizeof Char * aLength);
	myData.SetLength(Size() + aLength + 1);
	myData[myData.Size()] = L'\0';
}

void StringData::Append(ConstPtr<Char> aString)
{
	Append(aString, static_cast<i32>(wcslen(aString)));
}

void StringData::Append(ConstRef<String> aString)
{
	Append(aString.GetAddress(), aString.Size());
}

void StringData::MakeSizeFor(Const<i32> aAdditionalData)
{
	Const<i32> desiredSize = Size() + 1 + aAdditionalData;
	i32 capacity = Max(32, Capacity());
	while (desiredSize > capacity)
		capacity *= 2;
	if (capacity != Capacity())
		Reserve(capacity);
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

void StringData::AppendChar(Const<Char> aCharacter)
{
	CheckForReferences();

	myData.Add(L'\0');
	myData[Size() - 1] = aCharacter;
}

std::wostream & operator<<(Ref<std::wostream> aOut, ConstRef<StringData> aString)
{
	aOut.write(aString.GetAddress(), aString.Size());
	return aOut;
}

std::ostream & operator<<(Ref<std::ostream> aOut, ConstRef<StringData> aString)
{
	for (i32 i = 0; i < aString.Size(); ++i)
		aOut.write(reinterpret_cast<ConstPtr<char>>(&aString[i]), 1);
	return aOut;
}

void from_json(ConstRef<json> aNode, Ref<StringData> aString)
{
	aString = StringData(aNode.get<std::wstring>());
}

void to_json(Ref<json> aNode, ConstRef<StringData> aString)
{
	aNode = *aString;
}
