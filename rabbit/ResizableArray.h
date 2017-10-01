#pragma once

#include <cstdlib>
#include "Array.h"

class ResizableArrayBase
{
public:
	ResizableArrayBase();
	ResizableArrayBase(RValue<ResizableArrayBase> aOther);
	ResizableArrayBase(ConstRef<ResizableArrayBase> aOther);
	ResizableArrayBase(const size aSize, const bool aClearMemory = true);
	~ResizableArrayBase();

	Ref<ResizableArrayBase> operator=(RValue<ResizableArrayBase> aOther);
	Ref<ResizableArrayBase> operator=(ConstRef<ResizableArrayBase> aOther);

	size Size() const;

	void Resize(const size aSize, const bool aClearMemory = true);
	void Reserve(const size aSize, const bool aClearMemory = true);

	Ptr_v GetAddress();
	ConstPtr_v GetAddress() const;

private:
	Ptr_v myData;
	size mySize; // : sizeof Ptr; ?
};

template <typename T>
class ResizableArray
{
public:
	ResizableArray();
	ResizableArray(const size aLength, const bool aClearMemory = true);
	ResizableArray(RValue<ResizableArray<T>> aOther);
	ResizableArray(ConstRef<ResizableArray<T>> aOther);
	~ResizableArray();

	ResizableArray & operator=(RValue<ResizableArray<T>> aOther);
	ResizableArray & operator=(ConstRef<ResizableArray<T>> aOther);

	size Length() const;
	size SizeInBytes() const;

	void Resize(const size aLength, const bool aClearMemory = true);
	void Reserve(const size aLength, const bool aClearMemory = true);

	Ref<T> operator*();
	ConstRef<T> operator*() const;

	Ref<T> operator[](const u64 aIndex);
	ConstRef<T> operator[](const u64 aIndex) const;

private:
	ResizableArrayBase myData;
	size myLength;
};

template <typename T>
ResizableArray<T> & ResizableArray<T>::operator=(ConstRef<ResizableArray<T>> aOther)
{
	myData = aOther.myData;
	myLength = aOther.myLength;
	return *this;
}

template <typename T>
ResizableArray<T> & ResizableArray<T>::operator=(RValue<ResizableArray<T>> aOther)
{
	myData = std::move(aOther.myData);
	myLength = aOther.myLength;
#ifdef _DEBUG
	aOther.myLength = 0;
#endif
	return *this;
}

template <typename T>
ResizableArray<T>::ResizableArray(ConstRef<ResizableArray<T>> aOther)
	: ResizableArray()
{
	*this = aOther;
}

template <typename T>
ResizableArray<T>::ResizableArray(RValue<ResizableArray<T>> aOther)
	: ResizableArray()
{
	*this = std::move(aOther);
}

template <typename T>
size ResizableArray<T>::Length() const
{
	return myLength;
}

template <typename T>
size ResizableArray<T>::SizeInBytes() const
{
	return myData.Size();
}

template <typename T>
void ResizableArray<T>::Reserve(const size aLength, const bool aClearMemory /*= true*/)
{
	if (aLength >= myLength)
	{
		myData.Reserve(sizeof T * aLength, aClearMemory);
		myLength = aLength;
	}
}

template <typename T>
Ref<T> ResizableArray<T>::operator[](const u64 aIndex)
{
#ifdef _DEBUG
	if (aIndex >= myLength)
		abort();
#endif
	// TODO: Figure out why static cast won't do
	return *reinterpret_cast<Ptr<T>>(static_cast<Ptr<byte>>(myData.GetAddress()) + sizeof T * aIndex);
}

template <typename T>
ConstRef<T> ResizableArray<T>::operator[](const u64 aIndex) const
{
#ifdef _DEBUG
	if (aIndex >= myLength)
		abort();
#endif
	// TODO: Figure out why static cast won't do
	return *reinterpret_cast<ConstPtr<T>>(static_cast<ConstPtr<byte>>(myData.GetAddress()) + sizeof T * aIndex);
}

template <typename T>
ResizableArray<T>::ResizableArray()
{
}

template <typename T>
ResizableArray<T>::ResizableArray(const size aLength, const bool aClearMemory /*= true*/)
	: myData(aLength * sizeof T, aClearMemory)
{
	myLength = aLength;
}

template <typename T>
ResizableArray<T>::~ResizableArray()
{
}

template <typename T>
void ResizableArray<T>::Resize(const size aLength, const bool aClearMemory /*= true*/)
{
	myData.Resize(aLength * sizeof T, aClearMemory);
	myLength = aLength;
}

template <typename T>
Ref<T> ResizableArray<T>::operator*()
{
	return *static_cast<Ptr<T>>(myData.GetAddress());
}

template <typename T>
ConstRef<T> ResizableArray<T>::operator*() const
{
	return *static_cast<ConstPtr<T>>(myData.GetAddress());
}
