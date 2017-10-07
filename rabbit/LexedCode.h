#pragma once
#include "List.h"

class Lexeme;

class LexedCode
{
public:
	LexedCode();
	~LexedCode();

	LexedCode(RValue<LexedCode> aCopy);
	Ref<LexedCode> operator=(RValue<LexedCode> aCopy);

	// Not copyable
	LexedCode(ConstRef<LexedCode> aCopy) = delete;
	// Not copyable
	Ref<LexedCode> operator=(ConstRef<LexedCode> aCopy) = delete;
	
	template <typename TLexemeType>
	void Add(RValue<TLexemeType> aLexeme);

	void Clear();

private:
	void MakeSizeFor(Const<i32> aAdditionalData);

	ResizableArray<byte> myLexemeData;
	List<ConstPtr<Lexeme>> myLexemes;
	
	using MoveConstructor = void(*)(Const<Ptr<void>> aDestination, Const<Ptr<void>> aSource);
	List<MoveConstructor> myMoveConstructors;

	size myWritePosition;
};

template <typename T>
void Move(Const<Ptr<void>> aDestination, Const<Ptr<void>> aSource)
{
	Ptr<T> destination = reinterpret_cast<Ptr<T>>(aDestination);
	new (destination) T(std::move(*reinterpret_cast<Ptr<T>>(aSource)));
}

template <typename TLexemeType>
void LexedCode::Add(RValue<TLexemeType> aLexeme)
{
	// TODO: Move this assert to class scope
	static_assert(std::is_polymorphic_v<TLexemeType>, "Value must be polymorphic!");
	static_assert(std::is_move_constructible_v<TLexemeType>, "Value must be move constructible!");

	MakeSizeFor(sizeof TLexemeType);

	RawPtr ptr = &myLexemeData[myWritePosition];
	size_t freeSpace = myLexemeData.Size() - myWritePosition;
	Ptr<TLexemeType> aligned = reinterpret_cast<Ptr<TLexemeType>>(std::align(std::alignment_of_v<TLexemeType>, sizeof TLexemeType, ptr, freeSpace));
	myWritePosition += myLexemeData.Size() - freeSpace;
	new (aligned) TLexemeType(std::move(aLexeme));
	myWritePosition += sizeof TLexemeType;
	
	myLexemes.Add(aligned);
	myMoveConstructors.Add(Move<TLexemeType>);
}
