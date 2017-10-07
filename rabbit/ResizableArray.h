#pragma once

#include <cstdlib>
#include "Array.h"

class ResizableArrayBase
{
public:
	ResizableArrayBase();
	ResizableArrayBase(RValue<ResizableArrayBase> aOther);
	explicit ResizableArrayBase(ConstRef<ResizableArrayBase> aOther);
	ResizableArrayBase(Const<size> aSize, Const<bool> aClearMemory = true);
	~ResizableArrayBase();

	Ref<ResizableArrayBase> operator=(RValue<ResizableArrayBase> aOther);
	Ref<ResizableArrayBase> operator=(ConstRef<ResizableArrayBase> aOther) = delete;

	size Size() const;

	void Resize(Const<size> aSize, Const<bool> aClearMemory = true);
	
	Ptr<byte> GetAddress();
	ConstPtr<byte> GetAddress() const;

private:
	Ptr<byte> myData;
	size mySize; // : sizeof Ptr; ?
};

template <typename T>
class ResizableArray
{
public:
	ResizableArray();
	ResizableArray(Const<size> aLength, Const<bool> aClearMemory = true);
	ResizableArray(RValue<ResizableArray<T>> aOther);
	explicit ResizableArray(ConstRef<ResizableArray<T>> aOther);
	~ResizableArray();
	
	ResizableArray & operator=(RValue<ResizableArray<T>> aOther);
	ResizableArray & operator=(ConstRef<ResizableArray<T>> aOther) = delete;

	size Size() const;
	size SizeInBytes() const;

	void Resize(Const<size> aLength, Const<bool> aClearMemory = true);
	
	// Resets all elements to their original state
	void Reset();

	Ptr<T> GetAddress();
	ConstPtr<T> GetAddress() const;

	Ref<T> operator*();
	ConstRef<T> operator*() const;

	Ref<T> operator[](Const<u64> aIndex);
	ConstRef<T> operator[](Const<u64> aIndex) const;

private:
	ResizableArrayBase myData;
	size mySize;
};

template <typename T>
Ptr<T> ResizableArray<T>::GetAddress()
{
	return reinterpret_cast<Ptr<T>>(myData.GetAddress());
}

template <typename T>
ConstPtr<T> ResizableArray<T>::GetAddress() const
{
	return reinterpret_cast<ConstPtr<T>>(myData.GetAddress());
}

// template <typename T>
// ResizableArray<T> & ResizableArray<T>::operator=(ConstRef<ResizableArray<T>> aOther)
// {
// 	return *this;
// }

template <typename T>
ResizableArray<T> & ResizableArray<T>::operator=(RValue<ResizableArray<T>> aOther)
{
	myData = std::move(aOther.myData);
	mySize = aOther.mySize;
	aOther.mySize = 0;
	return *this;
}

template <typename T>
ResizableArray<T>::ResizableArray(ConstRef<ResizableArray<T>> aOther)
	: ResizableArray()
{
	myData = ResizableArrayBase(aOther.myData);
	mySize = aOther.mySize;
}

template <typename T>
ResizableArray<T>::ResizableArray(RValue<ResizableArray<T>> aOther)
	: ResizableArray()
{
	*this = std::move(aOther);
}

template <typename T>
size ResizableArray<T>::Size() const
{
	return mySize;
}

template <typename T>
size ResizableArray<T>::SizeInBytes() const
{
	return myData.Size();
}

template <typename T>
Ref<T> ResizableArray<T>::operator[](Const<size> aIndex)
{
#ifdef _DEBUG
	if (aIndex >= mySize)
		abort();
#endif
	return *(GetAddress() + aIndex);
}

template <typename T>
ConstRef<T> ResizableArray<T>::operator[](Const<size> aIndex) const
{
#ifdef _DEBUG
	if (aIndex >= mySize)
		abort();
#endif
	return *(GetAddress() + aIndex);
}

template <typename T>
ResizableArray<T>::ResizableArray()
{
	mySize = 0;
}

template <typename T>
ResizableArray<T>::ResizableArray(Const<size> aLength, Const<bool> aClearMemory /*= true*/)
	: myData(aLength * sizeof T, aClearMemory)
{
	mySize = aLength;

	for (size i = 0; i < aLength; ++i)
		new (myData.GetAddress() + i) T();
}

template <typename T>
void ResizableArray<T>::Reset()
{
	for (size i = 0; i < mySize; ++i)
		(*this)[i] = T();
}

template <typename T>
ResizableArray<T>::~ResizableArray()
{
}

template <typename T>
void ResizableArray<T>::Resize(Const<size> aLength, Const<bool> aClearMemory /*= true*/)
{
	myData.Resize(sizeof T * aLength, aClearMemory);
	mySize = aLength;
}

template <typename T>
Ref<T> ResizableArray<T>::operator*()
{
	return *reinterpret_cast<Ptr<T>>(myData.GetAddress());
}

template <typename T>
ConstRef<T> ResizableArray<T>::operator*() const
{
	return *reinterpret_cast<ConstPtr<T>>(myData.GetAddress());
}