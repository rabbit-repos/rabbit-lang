#include "pch.h"
#include "LexedCode.h"


LexedCode::LexedCode()
{
}


LexedCode::LexedCode(RValue<LexedCode> aMove)
	: LexedCode()
{
	*this = std::move(aMove);
}

Ref<LexedCode> LexedCode::operator=(RValue<LexedCode> aMove)
{
	myLexemes = std::move(aMove.myLexemes);
	return *this;
}

LexedCode LexedCode::Copy() const
{
	LexedCode copy;
	copy.myLexemes = myLexemes.Copy();
	return copy;
}

ConstRef<VirtualList<Lexeme>> LexedCode::GetLexemes() const
{
	return myLexemes;
}

LexedCode::~LexedCode()
{
}
