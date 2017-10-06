#include "pch.h"
#include "LexedCode.h"
#include "Lexeme.h"

LexedCode::LexedCode()
{
	myWritePosition = 0;

#ifdef _DEBUG
	myLexemeData.Resize(32);
#else
	myLexemeData.Resize(MegaByte * 10);
#endif
}

LexedCode::LexedCode(ConstRef<LexedCode> aCopy)
{
	*this = aCopy;
}

LexedCode::LexedCode(RValue<LexedCode> aCopy)
{
	*this = std::move(aCopy);
}

LexedCode::~LexedCode()
{
	for (i32 i = 0; i < myLexemes.Size(); ++i)
		delete myLexemes[i];
}

void LexedCode::MakeSizeFor(Const<i32> aAdditionalData)
{
	if (myWritePosition + aAdditionalData >= myLexemeData.Size())
	{
		ResizableArray<byte> newData;
		newData.Resize(myLexemeData.Size() * 2);

		for (i32 i = 0; i < myLexemes.Size(); ++i)
		{
			Const<i32> offset = static_cast<i32>(reinterpret_cast<ConstPtr<byte>>(myLexemes[i]) - myLexemeData.GetAddress());
#ifdef _DEBUG
			if (offset < 0 || static_cast<size>(offset) >= myLexemeData.Size())
				abort();
#endif
			myLexemes[i] = reinterpret_cast<ConstPtr<Lexeme>>(&newData[offset]);
		}

		myLexemeData = std::move(newData);
	}
}

Ref<LexedCode> LexedCode::operator=(ConstRef<LexedCode> aCopy)
{
	myLexemeData.Resize(aCopy.myLexemeData.Size());

	for (i32 i = 0; i < aCopy.myLexemes.Size(); ++i)
	{
		Const<i32> offset = static_cast<i32>(reinterpret_cast<ConstPtr<byte>>(aCopy.myLexemes[i]) - aCopy.myLexemeData.GetAddress());
#ifdef _DEBUG
		if (offset < 0 || static_cast<size>(offset) >= aCopy.myLexemeData.Size())
			abort();
#endif
		myLexemes[i] = reinterpret_cast<ConstPtr<Lexeme>>(&myLexemeData[offset]);
	}

	return *this;
}

Ref<LexedCode> LexedCode::operator=(RValue<LexedCode> aCopy)
{
	myLexemes = std::move(aCopy.myLexemes);
	myLexemeData = std::move(aCopy.myLexemeData);

	return *this;
}
