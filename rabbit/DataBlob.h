#pragma once

#include "Types.h"

template <size S, size C = 1>
class DataBlobBase
{
public:
	DataBlobBase();
	Ptr_v operator*();
	ConstPtr_v operator*() const;

	constexpr size Length() const;
	constexpr size Size() const;

private:
	byte myData[S][C];
};

template <size S, size C>
constexpr size DataBlobBase<S, C>::Size() const
{
	return S * C;
}

template <size S, size C>
DataBlobBase<S, C>::DataBlobBase()
{
	memset(&myData, 0, N);
}

template <size S, size C>
constexpr size DataBlobBase<S, C>::Length() const
{
	return C;
}

template <size S, size C>
Ptr_v DataBlobBase<S, C>::operator*()
{
	return &myData;
}

template <size S, size C>
ConstPtr_v DataBlobBase<S, C>::operator*() const
{
	return &myData;
}

template <typename T>
class DataBlob : public ResizableDataBlobBase
{
public:
	T & operator->();
	const T & operator->() const;
};

template <typename T>
T & DataBlob<T>::operator->()
{
	return *static_cast<Ptr<T>>(operator*());
}

template <typename T>
const T & DataBlob<T>::operator->() const
{
	return *static_cast<ConstPtr<T>>(*this);
}
