#pragma once
#include "Types.h"

class StringData;

class String
{
public:
	String();
	String(const String & aString, const i32 aNumberOfCharacters);
	String(ConstRef<StringData> aString);
	~String();

	i32 Length() const;
	ConstPtr<Char> GetAddress() const;
	
	ConstRef<Char> operator[](const i32 aIndex) const;

	String SubString(const i32 aStart, const i32 aLength);
	
	bool operator==(const char * aOther) const;
	bool operator!=(const char * aOther) const;
	bool operator==(const wchar_t * aOther) const;
	bool operator!=(const wchar_t * aOther) const;

	bool operator==(const String & aOther) const;
	bool operator!=(const String & aOther) const;

private:
	explicit String(ConstPtr<StringData> aOwner, ConstPtr<Char> aDataPoint, const i32 aLength);
	
	ConstPtr<Char> myData;
	i32 myLength;

#ifdef _DEBUG
	ConstPtr<StringData> myOwner;
#endif
};
