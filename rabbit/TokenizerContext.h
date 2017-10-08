#pragma once

class TokenizerContext
{
public:
	TokenizerContext(ConstPtr<StringData> aCode);
	TokenizerContext(ConstRef<TokenizerContext>) = delete;
	TokenizerContext(RValue<TokenizerContext>) = delete;
	Ref<TokenizerContext> operator=(ConstRef<TokenizerContext>) = delete;
	Ref<TokenizerContext> operator=(RValue<TokenizerContext>) = delete;
	~TokenizerContext();

	void AdvanceCursor();
	void AdvanceCursor(Const<i32> aAmount);

	i32 CursorLocation() const;

	Char At() const;
	Char At(Const<i32> aOffset) const;
	
	String Peek(Const<i32> aLength) const;
	String StringAt(Const<i32> aOffset, Const<i32> aSize) const;

	bool IsAtEnd() const;

private:
	ConstPtr<StringData> myCode;
	i32 myCursor;
};

inline Char TokenizerContext::At() const
{
	if (myCursor < 0 || myCursor >= myCode->Size())
		return L'\0';
	return (*myCode)[myCursor];
}

inline Char TokenizerContext::At(Const<i32> aOffset) const
{
	Const<i32> index = myCursor + aOffset;
	if (index < 0 || index >= myCode->Size())
		return L'\0';
	return (*myCode)[index];
}

inline i32 TokenizerContext::CursorLocation() const
{
	return myCursor;
}

inline void TokenizerContext::AdvanceCursor()
{
	if (!IsAtEnd())
		++myCursor;
}

inline void TokenizerContext::AdvanceCursor(Const<i32> aAmount)
{
	myCursor += aAmount;
	if (myCursor > myCode->Size())
		myCursor = myCode->Size();
}

inline bool TokenizerContext::IsAtEnd() const
{
	return myCursor >= myCode->Size();
}
