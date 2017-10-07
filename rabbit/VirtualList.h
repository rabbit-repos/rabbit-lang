#pragma once
#include "VirtualListHelper.h"

class Lexeme;

class VirtualList
{
public:
	VirtualList();
	~VirtualList();

	// static_assert(std::is_polymorphic_v<T>, "Type of VirtualList must be polymorphic!");
	// static_assert(std::has_virtual_destructor_v<T>, "Type of VirtualList must have a virtual desctructor!");

	VirtualList(RValue<VirtualList> aCopy);
	Ref<VirtualList> operator=(RValue<VirtualList> aCopy);

	// Use Copy() instead
	VirtualList(ConstRef<VirtualList> aCopy) = delete;
	// Use Copy() instead
	Ref<VirtualList> operator=(ConstRef<VirtualList> aCopy) = delete;
	
	Ref<Ptr<Lexeme>> operator[](Const<i32> aIndex);
	ConstRef<Ptr<Lexeme>> operator[](Const<i32> aIndex) const;

	template <typename TLexemeType>
	void Add(RValue<TLexemeType> aLexeme);

	i32 Size() const;
	void Clear();

private:
	void MakeSizeFor(Const<i32> aAdditionalData);

	ResizableArray<u8> myData;
	List<Ptr<Lexeme>> myObjects;
	
	using CopyFunction = void(*)(Const<Ptr<void>> aDestination, Const<Ptr<void>> aSource, Const<VirtualListCopyMode> aCopyMode);
	List<CopyFunction> myCopyFunctions;

	size myWritePosition;
};

template <typename TLexemeType>
void VirtualList::Add(RValue<TLexemeType> aLexeme)
{
	static_assert(std::is_move_constructible_v<TLexemeType>, "Types added to a VirtualList must be move constructible!");

	MakeSizeFor(sizeof TLexemeType);

	RawPtr ptr = &myData[myWritePosition];
	size_t freeSpace = myData.Size() - myWritePosition;
	std::align(std::alignment_of_v<TLexemeType>, sizeof TLexemeType, ptr, freeSpace);
	Ptr<TLexemeType> obj = reinterpret_cast<Ptr<TLexemeType>>(ptr);
	new (obj) TLexemeType(std::move(aLexeme));
	myWritePosition = (reinterpret_cast<Ptr<u8>>(ptr) - myData.GetAddress()) + sizeof TLexemeType;
	
	myObjects.Add(obj);
	myCopyFunctions.Add(VirtualCopyHelper<TLexemeType>);
}
