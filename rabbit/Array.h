#pragma once

#include "Types.h"

template <size S, size C = 1>
class ArrayBase
{
public:
	ArrayBase();
	Ptr_v operator*();
	ConstPtr_v operator*() const;

	constexpr size Count() const;
	constexpr size Size() const;

private:
	byte myData[S][C];
};

template <size S, size C>
ArrayBase<S, C>::ArrayBase()
{
	memset(&myData, 0, N);
}

template <size S, size C>
constexpr size ArrayBase<S, C>::Count() const
{
	return C;
}

template <size S, size C>
constexpr size ArrayBase<S, C>::Size() const
{
	return S * C;
}

template <size S, size C>
Ptr_v ArrayBase<S, C>::operator*()
{
	return &myData;
}

template <size S, size C>
ConstPtr_v ArrayBase<S, C>::operator*() const
{
	return &myData;
}

template <typename T, size C = 1>
class DataBlob : public ArrayBase<sizeof T, C>
{
public:
	Ref<T> operator->();
	ConstRef<T> operator->() const;

	Ref<T> operator[](const i32 aIndex);
	ConstRef<T> operator[](const i32 aIndex) const;
};

template <typename T, size C>
T & DataBlob<T, C>::operator->()
{
	return *static_cast<Ptr<T>>(operator*());
}

template <typename T, size C>
const T & DataBlob<T, C>::operator->() const
{
	return *static_cast<ConstPtr<T>>(*this);
}

template <typename T, size C /*= 1*/>
Ref<T> DataBlob<T, C>::operator[](const i32 aIndex)
{
	return *static_cast<Ptr<T>>((*this)[aIndex]);
}

template <typename T, size C /*= 1*/>
ConstRef<T> DataBlob<T, C>::operator[](const i32 aIndex) const
{
	return *static_cast<ConstPtr<T>>((*this)[aIndex]);
}
