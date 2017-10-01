#pragma once

#include <cstdlib>
#include "Array.h"

class ResizableArrayBase
{
public:
	ResizableArrayBase();
	ResizableArrayBase(const size aSize, const bool aClearMemory = true);
	~ResizableArrayBase();

	size Size() const;

	void Resize(const size aSize, const bool aClearMemory = true);
	void Reserve(const size aSize, const bool aClearMemory = true);

	Ptr_v GetAddress();
	const ConstPtr_v GetAddress() const;

private:
	Ptr_v myData;
	size mySize; // : sizeof Ptr; ?
};

template <typename T>
class List
{
public:
	List();
	List(const size aLength, const bool aClearMemory = true);
	~List();

	size Length() const;
	size SizeInBytes() const;

	void Resize(const size aLength, const bool aClearMemory = true);
	void Reserve(const size aLength, const bool aClearMemory = true);

	Ptr<T> operator*();
	ConstPtr<T> operator*() const;

	Ptr<T> operator[](const u64 aIndex);
	ConstPtr<T> operator[](const u64 aIndex) const;

private:
	ResizableArrayBase myData;
	size myLength;
};

template <typename T>
size List<T>::Length() const
{
	return myLength;
}

template <typename T>
size List<T>::SizeInBytes() const
{
	return myData.Size();
}

template <typename T>
void List<T>::Reserve(const size aLength, const bool aClearMemory /*= true*/)
{
	if (aLength >= myLength)
	{
		myData.Reserve(sizeof T * aLength, aClearMemory);
		myLength = aLength;
	}
}

template <typename T>
Ptr<T> List<T>::operator[](const u64 aIndex)
{
#ifdef _DEBUG
	if (aIndex >= myLength)
		abort();
#endif
	// TODO: Figure out why static cast won't do
	return reinterpret_cast<Ptr<T>>(static_cast<Ptr<byte>>(myData.GetAddress()) + sizeof T * aIndex);
}

template <typename T>
ConstPtr<T> List<T>::operator[](const u64 aIndex) const
{
#ifdef _DEBUG
	if (aIndex >= myLength)
		abort();
#endif
	// TODO: Figure out why static cast won't do
	return reinterpret_cast<ConstPtr<T>>(static_cast<ConstPtr<byte>>(myData.GetAddress()) + sizeof T * aIndex);
}

template <typename T>
List<T>::List()
{
}

template <typename T>
List<T>::List(const size aLength, const bool aClearMemory /*= true*/)
	: myData(aLength * sizeof T, aClearMemory)
{
	myLength = aLength;
}

template <typename T>
List<T>::~List()
{
}

template <typename T>
void List<T>::Resize(const size aLength, const bool aClearMemory /*= true*/)
{
	myData.Resize(aLength * sizeof T, aClearMemory);
	myLength = aLength;
}

template <typename T>
Ptr<T> List<T>::operator*()
{
	return static_cast<Ptr<T>>(myData.GetAddress());
}

template <typename T>
ConstPtr<T> List<T>::operator*() const
{
	return static_cast<ConstPtr<T>>(myData.GetAddress());
}
