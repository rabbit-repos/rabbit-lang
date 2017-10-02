#pragma once

template <size S, size N = 1>
class ArrayBase
{
public:
	ArrayBase(Const<bool> aClearMemory = true);
	
	Ptr<byte> GetAddress();
	ConstPtr<byte> GetAddress() const;

	constexpr size Count() const;
	constexpr size SizeInBytes() const;

private:
	byte myData[S * N];
};

template <size S, size N>
ArrayBase<S, N>::ArrayBase(Const<bool> aClearMemory/* = true*/)
{
	if (aClearMemory)
	{
		memset(&myData, 0, S * N);
	}
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
Ptr<byte> ArrayBase<S, N>::GetAddress()
{
	return static_cast<Ptr<byte>>(myData);
}

template <size S, size N>
ConstPtr<byte> ArrayBase<S, N>::GetAddress() const
{
	return static_cast<ConstPtr<byte>>(myData);
}

template <typename T, size N = 1>
class Array : public ArrayBase<sizeof T, N>
{
public:
	Ref<T> operator[](const i32 aIndex);
	ConstRef<T> operator[](const i32 aIndex) const;
};

template <typename T, size N /*= 1*/>
Ref<T> Array<T, N>::operator[](const i32 aIndex)
{
#ifdef _DEBUG
	if (aIndex < 0 || aIndex >= N)
		abort();
#endif
	return *reinterpret_cast<Ptr<T>>(ArrayBase::GetAddress() + sizeof T * aIndex);
}

template <typename T, size N /*= 1*/>
ConstRef<T> Array<T, N>::operator[](const i32 aIndex) const
{
#ifdef _DEBUG
	if (aIndex < 0 || aIndex >= N)
		abort();
#endif
	return *reinterpret_cast<ConstPtr<T>>(ArrayBase::GetAddress() + sizeof T * aIndex);
}
