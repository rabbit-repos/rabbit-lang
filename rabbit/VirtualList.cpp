#include "pch.h"
#include "VirtualList.h"
#include "Lexeme.h"

VirtualList::VirtualList()
{
	myWritePosition = 0;

#ifdef _DEBUG
	myData.Resize(32);
#else
	myData.Resize(MegaByte * 10);
#endif
}

VirtualList::VirtualList(RValue<VirtualList> aCopy)
{
	*this = std::move(aCopy);
}

void VirtualList::Clear()
{
	for (i32 i = 0; i < myObjects.Size(); ++i)
		myCopyFunctions[i](null, myObjects[i], VirtualListCopyMode::Destruct);
	myObjects.Clear();
	myWritePosition = 0;
}

VirtualList::~VirtualList()
{
	Clear();
}

void VirtualList::MakeSizeFor(Const<i32> aAdditionalData)
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
			myObjects[i] = reinterpret_cast<Ptr<Lexeme>>(&newData[offset]);
		}

		myData = std::move(newData);
	}
}

Ref<Ptr<Lexeme>> VirtualList::operator[](Const<i32> aIndex)
{
	return myObjects[aIndex];
}

ConstRef<Ptr<Lexeme>> VirtualList::operator[](Const<i32> aIndex) const
{
	return myObjects[aIndex];
}

i32 VirtualList::Size() const
{
	return myObjects.Size();
}

Ref<VirtualList> VirtualList::operator=(RValue<VirtualList> aCopy)
{
	myObjects = std::move(aCopy.myObjects);
	myData = std::move(aCopy.myData);

	return *this;
}
