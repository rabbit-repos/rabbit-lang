#pragma once
#include "List.h"

class String;

class StringData
{
public:
	StringData();
	explicit StringData(ConstPtr<Char> aString);
	explicit StringData(ConstRef<std::wstring> aString);
	explicit StringData(ConstRef<String> aString);
	StringData(ConstPtr<Char> aString, Const<i32> aLength);
	StringData(Const<i32> aExpectedLength);
	StringData(RValue<StringData> aOther);
	~StringData();

	Ref<StringData> operator=(RValue<StringData> aOther);

	StringData Copy() const;

	// Use Copy() instead
	StringData(ConstRef<StringData>) = delete;
	// Use Copy() instead
	Ref<StringData> operator=(ConstRef<StringData>) = delete;

	static StringData FromASCII(ConstPtr<char> aString);
	ConstPtr<Char> ToCString() const;

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

	void Append(ConstRef<String> aString);
	void Append(ConstPtr<Char> aString);
	void Append(ConstPtr<Char> aString, Const<i32> aLength);
	void Append(ConstRef<std::wstring> aString);
	void Append(Const<u64> aValue);
	void Append(Const<i64> aValue);
	void Append(Const<u32> aValue);
	void Append(Const<i32> aValue);
	void Append(Const<u16> aValue);
	void Append(Const<i16> aValue);
	void Append(Const<u8> aValue);
	void Append(Const<i8> aValue);
	void Append(Const<f32> aValue);
	void Append(Const<f64> aValue);


	void AppendChar(Const<Char> aCharacter, Const<i32> aRepeat = 1);

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

Ref<std::wostream> operator<<(Ref<std::wostream> aOut, ConstRef<StringData> aString);
Ref<std::ostream> operator<<(Ref<std::ostream> aOut, ConstRef<StringData> aString);

void from_json(ConstRef<json> aNode, Ref<StringData> aString);
void to_json(Ref<json> aNode, ConstRef<StringData> aString);
