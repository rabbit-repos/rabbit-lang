#pragma once
#include "List.h"

class String;

class StringData
{
public:
	StringData();
	explicit StringData(ConstPtr<Char> aString);
	explicit StringData(ConstRef<std::wstring> aString);
	StringData(ConstPtr<Char> aString, Const<i32> aLength);
	explicit StringData(ConstRef<String> aString);
	StringData(Const<i32> aExpectedLength);
	StringData(RValue<StringData> aOther);
	explicit StringData(ConstRef<StringData> aOther);
	~StringData();

	Ref<StringData> operator=(RValue<StringData> aOther);

	Ref<StringData> operator=(ConstRef<StringData> aOther) = delete;

	static StringData FromASCII(ConstPtr<char> aString);

	// TODO: Test if this can only be reached by literal strings (definition below)
	// template <size_t N>
	// MutableStringBlob(const Char aString[N]);

	void Resize(Const<i32> aLength);
	bool Reserve(Const<i32> aLength);
	
	i32 Size() const;
	i32 Capacity() const;

	Ref<Char> operator[](Const<i32> aIndex);
	ConstRef<Char> operator[](Const<i32> aIndex) const;

	Ref<Char> operator*();
	ConstRef<Char> operator*() const;

	Ptr<Char> GetAddress();
	ConstPtr<Char> GetAddress() const;

	void Append(ConstPtr<Char> aString);
	void Append(ConstPtr<Char> aString, Const<i32> aLength);
	void AppendChar(Const<Char> aCharacter);

private:
	List<Char> myData;

	void MakeSizeFor(Const<i32> aLength);
	void CheckForReferences() const;

#ifdef _DEBUG
	// me me bad boy (x2)
	friend String;
	mutable int32_t myNumReferences;
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
