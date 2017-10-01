#include "DataBlob.h"
#include <cstdlib>
#include <cstring>

ResizableDataBlobBase::ResizableDataBlobBase()
{
	myData = nullptr;
	mySize = 0;
}

ResizableDataBlobBase::ResizableDataBlobBase(const size aSize, const bool aClearMemory/* = true*/)
{
	if (aClearMemory)
		myData = calloc(1, aSize);
	else
		malloc(aSize);
	mySize = aSize;
}

ResizableDataBlobBase::~ResizableDataBlobBase()
{
	free(myData);

#ifdef _DEBUG
	myData = nullptr;
	mySize = 0;
#endif
}

void ResizableDataBlobBase::Resize(const size aSize, const bool aClearMemory/* = true*/)
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

Ptr_v ResizableDataBlobBase::operator*()
{
	return myData;
}

ConstPtr_v ResizableDataBlobBase::operator*() const
{
	return myData;
}

decltype(ResizableDataBlobBase::mySize) ResizableDataBlobBase::Length() const
{
	return mySize;
}
