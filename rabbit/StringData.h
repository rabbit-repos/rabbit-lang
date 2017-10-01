#pragma once

#include "Types.h"
#include "ResizableArray.h"

class StringData
{
public:
	StringData();
	StringData(ConstPtr<Char> aString);
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

private:
	ResizableArray<Char> myData;

	// me me bad boy
	friend class String;
	mutable size myNumReferences;
};

// template <size_t N>
// MutableStringBlob::MutableStringBlob(const Char aString[N])
// {
// 	myData.Resize(N, false);
// 	memcpy(*myData, aString, sizeof Char * N);
// }
