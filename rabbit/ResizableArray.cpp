#include "ResizableArray.h"
#include <cstdlib>
#include <cstring>
#include <xutility>

ResizableArrayBase::ResizableArrayBase()
{
	myData = null;
	mySize = 0;
}

ResizableArrayBase::ResizableArrayBase(const size aSize, const bool aClearMemory/* = true*/)
{
	if (aClearMemory)
		myData = calloc(1, aSize);
	else
		myData = malloc(aSize);

	if (!myData)
		abort();

	mySize = aSize;
}

ResizableArrayBase::ResizableArrayBase(RValue<ResizableArrayBase> aOther)
{
	*this = std::move(aOther);
}

ResizableArrayBase::ResizableArrayBase(ConstRef<ResizableArrayBase> aOther)
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
	
	if (aClearMemory && aSize > mySize)
		myData = calloc(1, aSize);
	else
		myData = malloc(aSize);

	if (!myData)
		abort();

	memcpy(myData, oldData, Min(mySize, aSize));
	mySize = aSize;

	free(oldData);
}

void ResizableArrayBase::Reserve(const size aSize, const bool aClearMemory /*= true*/)
{
	if (aSize > mySize)
		Resize(aSize, aClearMemory);
}

Ptr_v ResizableArrayBase::GetAddress()
{
	return myData;
}

const ConstPtr_v ResizableArrayBase::GetAddress() const
{
	return myData;
}

ResizableArrayBase & ResizableArrayBase::operator=(RValue<ResizableArrayBase> aOther)
{
	myData = std::move(aOther.myData);
	aOther.myData = null;
	mySize = aOther.mySize;
	return *this;
}

ResizableArrayBase & ResizableArrayBase::operator=(ConstRef<ResizableArrayBase> aOther)
{
	if (aOther.myData)
	{
		myData = malloc(aOther.mySize);
		if (!myData)
			abort();
		memcpy(myData, aOther.myData, aOther.mySize);
	}
	else
		myData = null;

	mySize = aOther.mySize;
	return *this;
}

size ResizableArrayBase::Size() const
{
	return mySize;
}
