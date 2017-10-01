#pragma once

class StringData;

class String
{
public:
	String();
	String(const String & aString, const i32 aNumberOfCharacters);
	String(ConstRef<StringData> aString);
	String(ConstPtr<Char> aString);
	~String();

	i32 Length() const;
	ConstPtr<Char> GetAddress() const;
	
	std::string ToASCII() const;
	std::wstring ToWideString() const;

	ConstRef<Char> operator[](const i32 aIndex) const;

	String SubString(const i32 aStart, const i32 aLength) const;
	String Trim() const;

	bool BeginsWith(ConstRef<String> aString) const;
	bool EndsWith(ConstRef<String> aString) const;

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

Ref<std::wostream> operator<<(Ref<std::wostream> aOut, ConstRef<String> aString);
Ref<std::ostream> operator<<(Ref<std::ostream> aOut, ConstRef<String> aString);
