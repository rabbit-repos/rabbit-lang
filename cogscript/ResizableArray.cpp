#include "pch.h"
#include "ResizableArray.h"
#include <cstdlib>
#include <cstring>
#include <xutility>

ResizableArrayBase::ResizableArrayBase()
{
	myData = null;
	mySize = 0;
}

ResizableArrayBase::ResizableArrayBase(Const<size> aSize, Const<bool> aClearMemory/* = true*/)
{
	if (aClearMemory)
		myData = static_cast<Ptr<u8>>(calloc(1, aSize));
	else
		myData = static_cast<Ptr<u8>>(malloc(aSize));

	if (!myData)
		FatalError();

	mySize = aSize;
}

ResizableArrayBase::ResizableArrayBase(RValue<ResizableArrayBase> aOther)
	: ResizableArrayBase()
{
	*this = std::move(aOther);
}

ResizableArrayBase ResizableArrayBase::Copy() const
{
	ResizableArrayBase copy;

	if (myData)
	{
		copy.myData = reinterpret_cast<Ptr<u8>>(malloc(mySize));
		if (!copy.myData)
			FatalError();
		memcpy(copy.myData, myData, mySize);
	}
	else
		copy.myData = null;

	copy.mySize = mySize;

	return copy;
}

ResizableArrayBase::~ResizableArrayBase()
{
	free(myData);
}

void ResizableArrayBase::Resize(Const<size> aSize, Const<bool> aClearMemory/* = true*/)
{
	Const<RawPtr> oldData = myData;
	
	if (aClearMemory && aSize > mySize)
		myData = static_cast<Ptr<u8>>(calloc(1, aSize));
	else
		myData = static_cast<Ptr<u8>>(malloc(aSize));

	if (!myData)
		FatalError();

	if (oldData)
	{
		memcpy(myData, oldData, Min(mySize, aSize));
		free(oldData);
	}

	mySize = aSize;
}

Ptr<u8> ResizableArrayBase::GetAddress()
{
	return myData;
}

ConstPtr<u8> ResizableArrayBase::GetAddress() const
{
	return myData;
}

Ref<ResizableArrayBase> ResizableArrayBase::operator=(RValue<ResizableArrayBase> aOther)
{
	free(myData);
	
	myData = std::move(aOther.myData);
	mySize = aOther.mySize;

	aOther.myData = null;
	aOther.mySize = 0;

	return *this;
}

size ResizableArrayBase::Size() const
{
	return mySize;
}
