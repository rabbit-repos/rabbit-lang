#pragma once
#include "ResizableArray.h"

template <typename T>
class List
{
public:
	List();
	List(Const<i32> aLength, Const<bool> aClearMemory = true);
	List(ConstRef<List> aOther);
	List(RValue<List> aOther);
	~List();

	Ref<List> operator=(ConstRef<List> aOther);
	Ref<List> operator=(RValue<List> aOther);

	void Add(ConstRef<T> aItem);

	void RemoveAtIndex(Const<i32> aIndex);

	i32 Length() const;
	i32 Capacity() const;
	
	void SetLength(Const<i32> aLength);
	void Resize(Const<i32> aLength, Const<bool> aClearMemory = true);
	void Reserve(Const<i32> aLength, Const<bool> aClearMemory = true);

	Ptr<T> GetAddress();
	ConstPtr<T> GetAddress() const;

	Ref<T> operator[](Const<i32> aIndex);
	ConstRef<T> operator[](Const<i32> aIndex) const;

private:
	ResizableArray<T> myData;

	// TODO: Store initial X items on "stack", like so:
	// Array<T, N> myStackCache;

	i32 myLength;
};

template <typename T>
Ref<List<T>> List<T>::operator=(RValue<List> aOther)
{
	myData = std::move(aOther.myData);
	myLength = aOther.myLength;
	aOther.myLength = 0;
	return *this;
}

template <typename T>
Ref<List<T>> List<T>::operator=(ConstRef<List> aOther)
{
	myData = aOther.myData;
	myLength = aOther.myLength;
	return *this;
}

template <typename T>
List<T>::List(RValue<List> aOther)
	: List()
{
	*this = std::move(aOther);
}

template <typename T>
List<T>::List(ConstRef<List> aOther)
	: List()
{
	*this = aOther;
}

template <typename T>
Ref<T> List<T>::operator[](Const<i32> aIndex)
{
	return myData[aIndex];
}

template <typename T>
ConstRef<T> List<T>::operator[](Const<i32> aIndex) const
{
	return myData[aIndex];
}

template <typename T>
Ptr<T> List<T>::GetAddress()
{
	return myData.GetAddress();
}

template <typename T>
ConstPtr<T> List<T>::GetAddress() const
{
	return myData.GetAddress();
}

template <typename T>
void List<T>::Resize(Const<i32> aLength, Const<bool> aClearMemory /*= true*/)
{
#ifdef _DEBUG
	if (aLength < 0)
		abort();
#endif

	myData.Resize(aLength, aClearMemory);
	myLength = aLength;
}

template <typename T>
void List<T>::Reserve(Const<i32> aLength, Const<bool> aClearMemory /*= true*/)
{
	myData.Reserve(aLength, aClearMemory);
}

template <typename T>
List<T>::List(Const<i32> aLength, Const<bool> aClearMemory /*= true*/)
	: myData(aLength, aClearMemory)
{
	myLength = 0;
}

template <typename T>
void List<T>::RemoveAtIndex(Const<i32> aIndex)
{
#ifdef _DEBUG
	if (myLength <= 0)
		abort();
#endif

	for (size i = aIndex + 1; i < myLength; ++i)
		std::move(myData[i], myData[i - 1]);
	
	--myLength;

	new (&myData[myLength]) T();
}

template <typename T>
void List<T>::Add(ConstRef<T> aItem)
{
	myLength++;
	if (myLength >= Capacity())
		Reserve(Max(8, Capacity() * 2));
	myData[myLength - 1] = aItem;
}

template <typename T>
List<T>::List()
{
	myLength = 0;
}

template <typename T>
List<T>::~List()
{
	for (i32 i = 0; i < Length(); ++i)
		myData[i].~T();
	myLength = 0;
}

template <typename T>
i32 List<T>::Length() const
{
	return myLength;
}

template <typename T>
i32 List<T>::Capacity() const
{
	return static_cast<i32>(myData.Length());
}

template <typename T>
void List<T>::SetLength(Const<i32> aLength)
{
#ifdef _DEBUG
	if (aLength < 0 || aLength > Capacity())
		abort();
#endif

	myLength = aLength;
}
