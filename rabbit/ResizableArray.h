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

	size Length() const;

	void Resize(const size aSize, const bool aClearMemory = true);
	void Reserve(const size aSize, const bool aClearMemory = true);

	Ptr<byte> GetAddress();
	ConstPtr<byte> GetAddress() const;

private:
	Ptr<byte> myData;
	size myLength; // : sizeof Ptr; ?
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

	Ptr<T> GetAddress();
	ConstPtr<T> GetAddress() const;

	Ref<T> operator*();
	ConstRef<T> operator*() const;

	Ref<T> operator[](const u64 aIndex);
	ConstRef<T> operator[](const u64 aIndex) const;

private:
	ResizableArrayBase myData;
	size myLength;
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
	aOther.myLength = 0;
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
	return myData.Length();
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
	return *reinterpret_cast<Ptr<T>>(myData.GetAddress() + sizeof T * aIndex);
}

template <typename T>
ConstRef<T> ResizableArray<T>::operator[](const u64 aIndex) const
{
#ifdef _DEBUG
	if (aIndex >= myLength)
		abort();
#endif
	return *reinterpret_cast<ConstPtr<T>>(myData.GetAddress() + sizeof T * aIndex);
}

template <typename T>
ResizableArray<T>::ResizableArray()
{
	myLength = 0;
}

template <typename T>
ResizableArray<T>::ResizableArray(const size aLength, const bool aClearMemory /*= true*/)
	: myData(aLength * sizeof T, aClearMemory)
{
	myLength = aLength;

	for (size i = 0; i < aLength; ++i)
		new (myData.GetAddress() + sizeof T * i) T();
}

template <typename T>
ResizableArray<T>::~ResizableArray()
{
}

template <typename T>
void ResizableArray<T>::Resize(const size aLength, const bool aClearMemory /*= true*/)
{
	myData.Resize(sizeof T * aLength, aClearMemory);
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
