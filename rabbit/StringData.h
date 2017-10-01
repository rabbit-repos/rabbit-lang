#pragma once

#include "Types.h"
#include "ResizableArray.h"
#include <fstream>

class String;

class StringData
{
public:
	StringData();
	StringData(ConstPtr<Char> aString);
	StringData(ConstPtr<Char> aString, const i32 aLength);
	StringData(ConstRef<String> aString);
	StringData(const size aExpectedLength);
	StringData(RValue<StringData> aOther);
	StringData(ConstRef<StringData> aOther);
	~StringData();

	Ref<StringData> operator=(RValue<StringData> aOther);
	Ref<StringData> operator=(ConstRef<StringData> aOther);

	static StringData FromASCII(const char * aString);

	// TODO: Test if this can only be reached  by literal strings
	// template <size_t N>
	// MutableStringBlob(const Char aString[N]);

	void Resize(const i32 aLength);
	i32 Length() const;

	Ref<Char> operator[](const i32 aIndex);
	ConstRef<Char> operator[](const i32 aIndex) const;

	Ref<Char> operator*();
	ConstRef<Char> operator*() const;

	Ptr<Char> GetAddress();
	ConstPtr<Char> GetAddress() const;

private:
	ResizableArray<Char> myData;

#ifdef _DEBUG
	// me me bad boy (x2)
	friend String;
	mutable size myNumReferences;
#endif
};

// template <size_t N>
// MutableStringBlob::MutableStringBlob(const Char aString[N])
// {
// 	myData.Resize(N, false);
// 	memcpy(*myData, aString, sizeof Char * N);
// }

Ref<std::wostream> operator<<(Ref<std::wostream> aOut, ConstRef<StringData> aString);
Ref<std::ostream> operator<<(Ref<std::ostream> aOut, ConstRef<StringData> aString);

void from_json(ConstRef<json> aNode, Ref<StringData> aString);
void to_json(Ref<json> aNode, ConstRef<StringData> aString);
