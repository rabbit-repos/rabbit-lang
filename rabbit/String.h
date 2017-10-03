#pragma once

class StringData;

class String
{
public:
	String();
	String(ConstRef<String> aString, Const<i32> aNumberOfCharacters);
	String(ConstRef<StringData> aString);
	String(ConstPtr<Char> aString);
	~String();

	i32 Length() const;
	ConstPtr<Char> GetAddress() const;
	
	std::string ToASCII() const;
	std::wstring ToWideString() const;

	ConstRef<Char> operator[](Const<i32> aIndex) const;

	String SubString(Const<i32> aStart, Const<i32> aLength) const;
	String Trim() const;

	bool BeginsWith(ConstRef<String> aString) const;
	bool EndsWith(ConstRef<String> aString) const;

	bool operator==(ConstPtr<char> aOther) const;
	bool operator!=(ConstPtr<char> aOther) const;
	bool operator==(ConstPtr<wchar_t> aOther) const;
	bool operator!=(ConstPtr<wchar_t> aOther) const;

	bool operator==(ConstRef<String> aOther) const;
	bool operator!=(ConstRef<String> aOther) const;

	// Equivalent to operator==
	bool Equals(ConstRef<String> aOther) const;
	bool EqualsIgnoreCase(ConstRef<String> aOther) const;

	String ChopLeft(Const<i32> aEnd) const;
	String ChopRight(Const<i32> aBegin) const;

	bool FindFirst(Const<Char> aChar, Out<i32> aIndex, Const<i32> aBeginAt = 0) const;
	bool FindLast(Const<Char> aChar, Out<i32> aIndex, Const<i32> aBeginAt = MaxOf<i32>) const;

private:
	explicit String(ConstPtr<StringData> aOwner, ConstPtr<Char> aDataPoint, const i32 aLength);
	String MakeView(Const<i32> aStart, Const<i32> aLength) const;

	ConstPtr<Char> myData;
	i32 myLength;

#ifdef _DEBUG
	ConstPtr<StringData> myOwner;
#endif
};

Ref<std::wostream> operator<<(Ref<std::wostream> aOut, ConstRef<String> aString);
Ref<std::ostream> operator<<(Ref<std::ostream> aOut, ConstRef<String> aString);
