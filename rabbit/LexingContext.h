#pragma once

class LexingContext
{
public:
	LexingContext(ConstPtr<StringData> aCode);
	LexingContext(ConstRef<LexingContext>) = delete;
	LexingContext(RValue<LexingContext>) = delete;
	Ref<LexingContext> operator=(ConstRef<LexingContext>) = delete;
	Ref<LexingContext> operator=(RValue<LexingContext>) = delete;
	~LexingContext();

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

inline Char LexingContext::At() const
{
	if (myCursor < 0 || myCursor >= myCode->Size())
		return L'\0';
	return (*myCode)[myCursor];
}

inline Char LexingContext::At(Const<i32> aOffset) const
{
	Const<i32> index = myCursor + aOffset;
	if (index < 0 || index >= myCode->Size())
		return L'\0';
	return (*myCode)[index];
}

inline i32 LexingContext::CursorLocation() const
{
	return myCursor;
}

inline void LexingContext::AdvanceCursor()
{
	if (!IsAtEnd())
		++myCursor;
}

inline void LexingContext::AdvanceCursor(Const<i32> aAmount)
{
	myCursor += aAmount;
	if (myCursor > myCode->Size())
		myCursor = myCode->Size();
}

inline bool LexingContext::IsAtEnd() const
{
	return myCursor >= myCode->Size();
}
