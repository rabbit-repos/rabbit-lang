#pragma once
#include "Types.h"

class MutableStringData;

class String
{
public:
	String();
	String(const String & aString, const i32 aNumberOfCharacters);
	String(ConstRef<MutableStringData> aString);
	~String();

	i32 Length() const;
	ConstPtr<Char> GetAddress() const;
	
	ConstRef<Char> operator[](const i32 aIndex) const;

	String SubString(const i32 aStart, const i32 aLength);

private:
	explicit String(ConstPtr<Char> aDataPoint, const i32 aLength);

	ConstPtr<Char> myData;
	i32 myLength;
};
