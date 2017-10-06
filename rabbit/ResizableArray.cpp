#include "pch.h"
#include "ResizableArray.h"
#include <cstdlib>
#include <cstring>
#include <xutility>

ResizableArrayBase::ResizableArrayBase()
{
	myData = null;
	myLength = 0;
}

ResizableArrayBase::ResizableArrayBase(const size aSize, const bool aClearMemory/* = true*/)
	: ResizableArrayBase()
{
	if (aClearMemory)
		myData = static_cast<Ptr<byte>>(calloc(1, aSize));
	else
		myData = static_cast<Ptr<byte>>(malloc(aSize));

	if (!myData)
		abort();

	myLength = aSize;
}

ResizableArrayBase::ResizableArrayBase(RValue<ResizableArrayBase> aOther)
	: ResizableArrayBase()
{
	*this = std::move(aOther);
}

ResizableArrayBase::ResizableArrayBase(ConstRef<ResizableArrayBase> aOther)
	: ResizableArrayBase()
{
	*this = aOther;
}

ResizableArrayBase::~ResizableArrayBase()
{
	free(myData);
}

void ResizableArrayBase::Resize(const size aSize, const bool aClearMemory/* = true*/)
{
	const RawPtr oldData = myData;
	
	if (aClearMemory && aSize > myLength)
		myData = static_cast<Ptr<byte>>(calloc(1, aSize));
	else
		myData = static_cast<Ptr<byte>>(malloc(aSize));

	if (!myData)
		abort();

	if (oldData)
	{
		memcpy(myData, oldData, Min(myLength, aSize));
		free(oldData);
	}

	myLength = aSize;
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
	myLength = aOther.myLength;

	aOther.myData = null;
	aOther.myLength = 0;

	return *this;
}

Ref<ResizableArrayBase> ResizableArrayBase::operator=(ConstRef<ResizableArrayBase> aOther)
{
	free(myData);

	if (aOther.myData)
	{
		myData = reinterpret_cast<Ptr<byte>>(malloc(aOther.myLength));
		if (!myData)
			abort();
		memcpy(myData, aOther.myData, aOther.myLength);
	}
	else
		myData = null;

	myLength = aOther.myLength;

	return *this;
}

size ResizableArrayBase::Length() const
{
	return myLength;
}
