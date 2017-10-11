#pragma once

#include <cstdlib>
#include "Array.h"

class ResizableArrayBase
{
public:
	ResizableArrayBase();
	ResizableArrayBase(Const<size> aSize, Const<bool> aClearMemory = true);
	~ResizableArrayBase();

	ResizableArrayBase(RValue<ResizableArrayBase> aOther);
	Ref<ResizableArrayBase> operator=(RValue<ResizableArrayBase> aOther);
	
	// Use Copy() instead
	ResizableArrayBase(ConstRef<ResizableArrayBase> aOther) = delete;
	// Use Copy() instead
	Ref<ResizableArrayBase> operator=(ConstRef<ResizableArrayBase> aOther) = delete;

	ResizableArrayBase Copy() const;

	size Size() const;

	void Resize(Const<size> aSize, Const<bool> aClearMemory = true);
	
	Ptr<u8> GetAddress();
	ConstPtr<u8> GetAddress() const;

private:
	Ptr<u8> myData;
	size mySize;
};

template <typename T>
class ResizableArray
{
public:
	ResizableArray();
	ResizableArray(Const<size> aLength);
	~ResizableArray();
	
	ResizableArray(RValue<ResizableArray<T>> aOther);
	ResizableArray & operator=(RValue<ResizableArray<T>> aOther);
	
	// Use Copy() instead
	ResizableArray(ConstRef<ResizableArray<T>> aOther) = delete;
	// Use Copy() instead
	ResizableArray & operator=(ConstRef<ResizableArray<T>> aOther) = delete;

	ResizableArray Copy() const;

	size Size() const;
	size SizeInBytes() const;

	void Resize(Const<size> aLength);
	
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

template <typename T>
ResizableArray<T>::ResizableArray(RValue<ResizableArray<T>> aOther)
	: ResizableArray()
{
	*this = std::move(aOther);
}

template <typename T>
ResizableArray<T> & ResizableArray<T>::operator=(RValue<ResizableArray<T>> aOther)
{
	myData = std::move(aOther.myData);
	mySize = aOther.mySize;
	aOther.mySize = 0;
	return *this;
}

template <typename T>
ResizableArray<T> ResizableArray<T>::Copy() const
{
	ResizableArray copy;
	copy.Resize(Size());
	for (size i = 0; i < Size(); ++i)
		new (&copy[i]) T((*this)[i]);
	return copy;
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
ResizableArray<T>::ResizableArray(Const<size> aLength)
	: myData(aLength * sizeof T, false)
{
	mySize = aLength;

	for (size i = 0; i < aLength; ++i)
		new (GetAddress() + i) T();
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
void ResizableArray<T>::Resize(Const<size> aLength)
{
	Const<size> oldSize = mySize;
	myData.Resize(sizeof T * aLength, false);
	for (size i = oldSize; i < aLength; ++i)
		new (GetAddress() + i) T();
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