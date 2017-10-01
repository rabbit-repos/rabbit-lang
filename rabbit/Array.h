#pragma once

template <size S, size N = 1>
class ArrayBase
{
public:
	ArrayBase();
	Ptr_v operator*();
	ConstPtr_v operator*() const;

	constexpr size Count() const;
	constexpr size SizeInBytes() const;

private:
	byte myData[S][N];
};

template <size S, size N>
ArrayBase<S, N>::ArrayBase()
{
	memset(&myData, 0, N);
}

template <size S, size N>
constexpr size ArrayBase<S, N>::Count() const
{
	return N;
}

template <size S, size N>
constexpr size ArrayBase<S, N>::SizeInBytes() const
{
	return S * N;
}

template <size S, size N>
Ptr_v ArrayBase<S, N>::operator*()
{
	return &myData;
}

template <size S, size N>
ConstPtr_v ArrayBase<S, N>::operator*() const
{
	return &myData;
}

template <typename T, size N = 1>
class Array : public ArrayBase<sizeof T, N>
{
public:
	Ref<T> operator->();
	ConstRef<T> operator->() const;

	Ref<T> operator[](const i32 aIndex);
	ConstRef<T> operator[](const i32 aIndex) const;
};

template <typename T, size N>
T & Array<T, N>::operator->()
{
	return *static_cast<Ptr<T>>(operator*());
}

template <typename T, size N>
const T & Array<T, N>::operator->() const
{
	return *static_cast<ConstPtr<T>>(*this);
}

template <typename T, size N /*= 1*/>
Ref<T> Array<T, N>::operator[](const i32 aIndex)
{
	return *static_cast<Ptr<T>>((*this)[aIndex]);
}

template <typename T, size N /*= 1*/>
ConstRef<T> Array<T, N>::operator[](const i32 aIndex) const
{
	return *static_cast<ConstPtr<T>>((*this)[aIndex]);
}
