#pragma once
#include "VirtualListHelper.h"

template <typename T>
class VirtualList
{
public:
	VirtualList();
	~VirtualList();

	static_assert(std::is_polymorphic_v<T>, "Value inside of VirtualList must be polymorphic!");
	static_assert(std::has_virtual_destructor_v<T>, "Value of VirtualList must have a virtual destructor! (virtual T::~T())");

	VirtualList(RValue<VirtualList> aCopy);
	Ref<VirtualList> operator=(RValue<VirtualList> aCopy);

	// Use Copy() instead
	VirtualList(ConstRef<VirtualList> aCopy) = delete;
	// Use Copy() instead
	Ref<VirtualList> operator=(ConstRef<VirtualList> aCopy) = delete;

	VirtualList Copy() const;

	Ref<Ptr<T>> operator[](Const<i32> aIndex);
	ConstRef<Ptr<T>> operator[](Const<i32> aIndex) const;

	template <typename TDerivedType>
	void Add(RValue<TDerivedType> aLexeme);

	i32 Size() const;
	void Clear();

private:
	void MakeSizeFor(Const<i32> aAdditionalData);

	ResizableArray<u8> myData;
	List<Ptr<T>> myObjects;
	
	using CopyFunction = void(*)(Const<Ptr<void>> aDestination, Ptr<void> aSource, Const<VirtualListCopyMode> aCopyMode);
	List<CopyFunction> myCopyFunctions;

	size myWritePosition;
};

template <typename T>
VirtualList<T> VirtualList<T>::Copy() const
{
	VirtualList copy;
	copy.myData.Resize(myData.Size());
	copy.myObjects.Resize(myObjects.Size());

	for (i32 i = 0; i < myObjects.Size(); ++i)
	{
		Const<ptrdiff> offset = static_cast<ptrdiff>(reinterpret_cast<ConstPtr<u8>>(myObjects[i]) - myData.GetAddress());
#ifdef _DEBUG
		if (offset < 0 || static_cast<size>(offset) >= myData.Size())
			FatalError();
#endif
		myCopyFunctions[i](&copy.myData[offset], const_cast<Ptr<u8>>(&myData[offset]), VirtualListCopyMode::CopyConstruct);
	}

	copy.myCopyFunctions = myCopyFunctions.Copy();
	copy.myWritePosition = myWritePosition;

	return copy;
}

template <typename T>
VirtualList<T>::VirtualList()
{
	myWritePosition = 0;

#ifdef _DEBUG
	myData.Resize(32);
#else
	myData.Resize(MegaByte / 2);
#endif
}

template <typename T>
VirtualList<T>::VirtualList(RValue<VirtualList> aCopy)
{
	*this = std::move(aCopy);
}

template <typename T>
void VirtualList<T>::Clear()
{
	for (i32 i = 0; i < myObjects.Size(); ++i)
		myCopyFunctions[i](null, myObjects[i], VirtualListCopyMode::Destruct);
	myCopyFunctions.Clear();
	myObjects.Clear();
	myWritePosition = 0;
}

template <typename T>
VirtualList<T>::~VirtualList()
{
	Clear();
}

template <typename T>
void VirtualList<T>::MakeSizeFor(Const<i32> aAdditionalData)
{
	while (myWritePosition + aAdditionalData >= myData.Size())
	{
		ResizableArray<u8> newData;
		newData.Resize(myData.Size() * 2);

		for (i32 i = 0; i < myObjects.Size(); ++i)
		{
			Const<ptrdiff> offset = static_cast<ptrdiff>(reinterpret_cast<ConstPtr<u8>>(myObjects[i]) - myData.GetAddress());
#ifdef _DEBUG
			if (offset < 0 || static_cast<size>(offset) >= myData.Size())
				abort();
#endif
			myCopyFunctions[i](&newData[offset], &myData[offset], VirtualListCopyMode::MoveConstruct);
			myCopyFunctions[i](null, &myData[offset], VirtualListCopyMode::Destruct);
			myObjects[i] = reinterpret_cast<Ptr<T>>(&newData[offset]);
		}

		myData = std::move(newData);
	}
}

template <typename T>
Ref<Ptr<T>> VirtualList<T>::operator[](Const<i32> aIndex)
{
	return myObjects[aIndex];
}

template <typename T>
ConstRef<Ptr<T>> VirtualList<T>::operator[](Const<i32> aIndex) const
{
	return myObjects[aIndex];
}

template <typename T>
i32 VirtualList<T>::Size() const
{
	return myObjects.Size();
}

template <typename T>
Ref<VirtualList<T>> VirtualList<T>::operator=(RValue<VirtualList> aCopy)
{
	myObjects = std::move(aCopy.myObjects);
	myCopyFunctions = std::move(aCopy.myCopyFunctions);
	myData = std::move(aCopy.myData);

	return *this;
}


template <typename T>
template <typename TDerivedType>
void VirtualList<T>::Add(RValue<TDerivedType> aObject)
{
	static_assert(std::is_move_constructible_v<TDerivedType>, "Types added to a VirtualList must be move constructible!");
	static_assert(std::is_move_assignable_v<TDerivedType>, "Value of VirtualList must be move assignable! (operator=(&&))");
	static_assert(std::is_copy_constructible_v<TDerivedType>, "Value of VirtualList must be copy constructible! (BaseType(const&))");
	static_assert(std::is_base_of_v<T, TDerivedType>, "Type added to VirtualList must derive from the VirtualList's type!");

	MakeSizeFor(sizeof TDerivedType);

	RawPtr ptr = &myData[myWritePosition];
	size_t freeSpace = myData.Size() - myWritePosition;
	std::align(std::alignment_of_v<TDerivedType>, sizeof TDerivedType, ptr, freeSpace);
	Ptr<TDerivedType> obj = reinterpret_cast<Ptr<TDerivedType>>(ptr);
	new (obj) TDerivedType(std::move(aObject));
	myWritePosition = (reinterpret_cast<Ptr<u8>>(ptr) - myData.GetAddress()) + sizeof TDerivedType;
	
	myObjects.Add(obj);
	myCopyFunctions.Add(VirtualCopyHelper<TDerivedType>);
}
