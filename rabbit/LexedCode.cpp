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

LexedCode::LexedCode(RValue<LexedCode> aCopy)
{
	*this = std::move(aCopy);
}

void LexedCode::Clear()
{
	for (i32 i = 0; i < myLexemes.Size(); ++i)
		myLexemes[i]->~Lexeme();
	myLexemes.Clear();
	myWritePosition = 0;
}

LexedCode::~LexedCode()
{
	Clear();
}

void LexedCode::MakeSizeFor(Const<i32> aAdditionalData)
{
	while (myWritePosition + aAdditionalData >= myLexemeData.Size())
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
			myMoveConstructors[i](&newData[offset], &myLexemeData[offset]);
			myLexemes[i] = reinterpret_cast<ConstPtr<Lexeme>>(newData[offset]);
		}

		myLexemeData = std::move(newData);
	}
}

Ref<LexedCode> LexedCode::operator=(RValue<LexedCode> aCopy)
{
	myLexemes = std::move(aCopy.myLexemes);
	myLexemeData = std::move(aCopy.myLexemeData);

	return *this;
}
