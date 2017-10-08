#pragma once
#include "VirtualList.h"
#include "Lexeme.h"

class LexedCode
{
public:
	LexedCode();
	~LexedCode();

	LexedCode(RValue<LexedCode> aMove);
	Ref<LexedCode> operator=(RValue<LexedCode> aMove);

	// Use Copy() instead
	LexedCode(ConstRef<LexedCode>) = delete;
	// Use Copy() instead
	Ref<LexedCode> operator=(ConstRef<LexedCode>) = delete;

	LexedCode Copy() const;

	ConstRef<VirtualList<Lexeme>> GetLexemes() const;

	class LexemeListAccesser
	{
		friend class Interpreter;
		template <typename T>
		void AddLexeme(RValue<T> aLexeme);
	};

private:
	VirtualList<Lexeme> myLexemes;
};

template <typename T>
void LexedCode::LexemeListAccesser::AddLexeme(RValue<T> aLexeme)
{
	myLexemes.Add(myLexemes);
}
