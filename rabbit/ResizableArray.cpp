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
		myData = static_cast<Ptr<byte>>(calloc(1, aSize));
	else
		myData = static_cast<Ptr<byte>>(malloc(aSize));

	if (!myData)
		abort();

	mySize = aSize;
}

ResizableArrayBase::ResizableArrayBase(RValue<ResizableArrayBase> aOther)
	: ResizableArrayBase()
{
	*this = std::move(aOther);
}

ResizableArrayBase::ResizableArrayBase(ConstRef<ResizableArrayBase> aOther)
{
	if (aOther.myData)
	{
		myData = reinterpret_cast<Ptr<byte>>(malloc(aOther.mySize));
		if (!myData)
			abort();
		memcpy(myData, aOther.myData, aOther.mySize);
	}
	else
		myData = null;

	mySize = aOther.mySize;
}

ResizableArrayBase::~ResizableArrayBase()
{
	free(myData);
}

void ResizableArrayBase::Resize(Const<size> aSize, Const<bool> aClearMemory/* = true*/)
{
	Const<RawPtr> oldData = myData;
	
	if (aClearMemory && aSize > mySize)
		myData = static_cast<Ptr<byte>>(calloc(1, aSize));
	else
		myData = static_cast<Ptr<byte>>(malloc(aSize));

	if (!myData)
		abort();

	if (oldData)
	{
		memcpy(myData, oldData, Min(mySize, aSize));
		free(oldData);
	}

	mySize = aSize;
}

Ptr<byte> ResizableArrayBase::GetAddress()
{
	return myData;
}

ConstPtr<byte> ResizableArrayBase::GetAddress() const
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

// Ref<ResizableArrayBase> ResizableArrayBase::operator=(ConstRef<ResizableArrayBase> aOther)
// {
// 	return *this;
// }

size ResizableArrayBase::Size() const
{
	return mySize;
}
