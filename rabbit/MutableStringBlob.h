#pragma once

#include "Types.h"
#include "ResizableArray.h"

class MutableStringBlob
{
public:
	MutableStringBlob();
	MutableStringBlob(const Char * aString);
	MutableStringBlob(const size aExpectedLength);
	
	static MutableStringBlob FromASCII(const char * aString);

	// TODO: Test if this can only be reached  by literal strings
	// template <size_t N>
	// MutableStringBlob(const Char aString[N]);

	void Resize(const i32 aLength);
	i32 Length() const;

	Ptr<Char> operator[](const i32 aIndex);
	ConstPtr<Char> operator[](const i32 aIndex) const;

	Ptr<Char> operator*();
	ConstPtr<Char> operator*() const;

private:
	List<Char> myData;
};

// template <size_t N>
// MutableStringBlob::MutableStringBlob(const Char aString[N])
// {
// 	myData.Resize(N, false);
// 	memcpy(*myData, aString, sizeof Char * N);
// }
