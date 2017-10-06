#pragma once
#include "List.h"

class Lexeme;

class LexedCode
{
public:
	LexedCode();
	LexedCode(ConstRef<LexedCode> aCopy);
	LexedCode(RValue<LexedCode> aCopy);
	~LexedCode();

	Ref<LexedCode> operator=(ConstRef<LexedCode> aCopy);
	Ref<LexedCode> operator=(RValue<LexedCode> aCopy);

	template <typename TLexemeType>
	void AddLexeme(ConstRef<TLexemeType> aLexeme);

private:
	void MakeSizeFor(Const<i32> aAdditionalData);

	ResizableArray<byte> myLexemeData;
	List<ConstPtr<Lexeme>> myLexemes;
	size myWritePosition;
};

template <typename TLexemeType>
void LexedCode::AddLexeme(ConstRef<TLexemeType> aLexeme)
{
	std::cout << alignment_of_v<TLexemeType> << std::endl;

}
