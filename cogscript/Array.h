#pragma once
#include <type_traits>

template <size S, size N = 1>
class ArrayBase
{
public:
	ArrayBase(Const<bool> aClearMemory = true);
	
	Ptr<u8> GetAddress();
	ConstPtr<u8> GetAddress() const;

	constexpr size Count() const;
	constexpr size SizeInBytes() const;

protected:
	u8 myData[S * N];
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
Ptr<u8> ArrayBase<S, N>::GetAddress()
{
	return static_cast<Ptr<u8>>(myData);
}

template <size S, size N>
ConstPtr<u8> ArrayBase<S, N>::GetAddress() const
{
	return static_cast<ConstPtr<u8>>(myData);
}

template <typename T, size N = 1>
class Array : protected ArrayBase<sizeof T, N>
{
public:
	Array();
	Array(ConstRef<Array> aArray);
	Array(RValue<Array> aArray);
	~Array();

	Ref<Array> operator=(ConstRef<Array> aArray);
	Ref<Array> operator=(RValue<Array> aArray);

	Ref<T> operator[](const i32 aIndex);
	ConstRef<T> operator[](const i32 aIndex) const;
};

template <typename T, size N /*= 1*/>
Array<T, N>::Array(ConstRef<Array> aArray)
	: ArrayBase(false)
{
	Const<size> num = N * sizeof T;
	for (size i = 0; i < num; i += sizeof T)
		new (&(*this)[i]) T(aArray[i]);
}

template <typename T, size N /*= 1*/>
Array<T, N>::Array(RValue<Array> aArray)
{
	Const<size> num = N * sizeof T;
	for (size i = 0; i < num; i += sizeof T)
	{
		new (&(*this)[i]) T(std::move(aArray[i]));
		aArray[i].~T();
	}
}

template <typename T, size N /*= 1*/>
Ref<Array<T, N>> Array<T, N>::operator=(ConstRef<Array> aArray)
{
	Const<size> num = N * sizeof T;
	for (size i = 0; i < num; i += sizeof T)
	{
		(*this)[i].~T();
		new (&(*this)[i]) T(aArray[i]);
	}
	return *this;
}

template <typename T, size N /*= 1*/>
Ref<Array<T, N>> Array<T, N>::operator=(RValue<Array> aArray)
{
	Const<size> num = N * sizeof T;
	for (size i = 0; i < num; i += sizeof T)
	{
		(*this)[i].~T();
		new (&(*this)[i]) T(std::move(aArray[i]));
		aArray[i ].~T();
	}
	return *this;
}

template <typename T, size N /*= 1*/>
Array<T, N>::Array()
	: ArrayBase(std::is_trivially_default_constructible_v<T>)
{
	Const<size> num = N * sizeof T;

#pragma warning ( suppress : 4127 )
	if (std::is_trivially_default_constructible_v<T> == false)
		for (size i = 0; i < num; i += sizeof T)
			new (&myData[i]) T();
}

template <typename T, size N /*= 1*/>
Array<T, N>::~Array()
{
	Const<size> num = N * sizeof T;

#pragma warning ( suppress : 4127 )
	if (std::is_trivially_destructible_v<T> == false)
		for (size i = 0; i < num; i += sizeof T)
			reinterpret_cast<T*>(&myData[i])->~T();
#ifdef _DEBUG
	memset(myData, 0, sizeof myData);
#endif
}

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
