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
		myData = calloc(1, aSize);
	else
		myData = malloc(aSize);

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
	const Ptr_v oldData = myData;
	
	if (aClearMemory && aSize > myLength)
		myData = calloc(1, aSize);
	else
		myData = malloc(aSize);

	if (!myData)
		abort();

	memcpy(myData, oldData, Min(myLength, aSize));
	myLength = aSize;

	free(oldData);
}

void ResizableArrayBase::Reserve(const size aSize, const bool aClearMemory /*= true*/)
{
	if (aSize > myLength)
		Resize(aSize, aClearMemory);
}

Ptr_v ResizableArrayBase::GetAddress()
{
	return myData;
}

ConstPtr_v ResizableArrayBase::GetAddress() const
{
	return myData;
}

Ref<ResizableArrayBase> ResizableArrayBase::operator=(RValue<ResizableArrayBase> aOther)
{
	free(myData);
	myData = std::move(aOther.myData);
	aOther.myData = null;
	aOther.myLength = 0;
	myLength = aOther.myLength;
	return *this;
}

Ref<ResizableArrayBase> ResizableArrayBase::operator=(ConstRef<ResizableArrayBase> aOther)
{
	if (aOther.myData)
	{
		myData = malloc(aOther.myLength);
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
