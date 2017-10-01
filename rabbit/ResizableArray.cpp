#include "ResizableArray.h"
#include <cstdlib>
#include <cstring>

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

ResizableArrayBase::~ResizableArrayBase()
{
	free(myData);

#ifdef _DEBUG
	myData = null;
	mySize = 0;
#endif
}

void ResizableArrayBase::Resize(const size aSize, const bool aClearMemory/* = true*/)
{
	const Ptr_v oldData = myData;
	
	if (aClearMemory)
		myData = calloc(1, aSize);
	else
		myData = malloc(aSize);

	if (!myData)
		abort();

	memcpy(myData, oldData, Min(mySize, aSize));
	mySize = aSize;
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

size ResizableArrayBase::Size() const
{
	return mySize;
}
