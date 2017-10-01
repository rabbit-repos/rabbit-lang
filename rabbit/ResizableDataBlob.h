#pragma once
#include "DataBlob.h"

class ResizableDataBlobBase
{
public:
	ResizableDataBlobBase();
	ResizableDataBlobBase(const size aSize, const bool aClearMemory = true);
	virtual ~ResizableDataBlobBase();

	void Resize(const size aSize, const bool aClearMemory = true);

	Ptr_v operator*();
	ConstPtr_v operator*() const;

private:
	Ptr_v myData;
	size mySize; // : sizeof Ptr; ?

public:
	decltype(mySize) Length() const;
};

template <typename T>
class ResizableDataBlob
{
public:
	ResizableDataBlob();
	ResizableDataBlob(const size aSize, const bool aClearMemory = true);
	~ResizableDataBlob();

private:
	ResizableDataBlobBase<T> myBase;
};

