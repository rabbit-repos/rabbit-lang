#pragma once
#include "ResizableArray.h"

template <typename T>
class List
{
public:
	List();
	List(Const<i32> aLength, Const<bool> aClearMemory = true);
	explicit List(ConstRef<List> aOther);
	List(RValue<List> aOther);
	~List();

	Ref<List> operator=(ConstRef<List> aOther) = delete;
	Ref<List> operator=(RValue<List> aOther);

	void Add(ConstRef<T> aItem);
	void Add(RValue<T> aItem);

	void RemoveAtIndex(Const<i32> aIndex);
	void Clear();

	i32 Size() const;
	i32 Capacity() const;
	
	void SetLength(Const<i32> aLength);
	void Resize(Const<i32> aLength, Const<bool> aClearMemory = true);
	bool Reserve(Const<i32> aLength, Const<bool> aClearMemory = true);

	Ptr<T> GetAddress();
	ConstPtr<T> GetAddress() const;

	Ref<T> operator[](Const<i32> aIndex);
	ConstRef<T> operator[](Const<i32> aIndex) const;

private:
	ResizableArray<T> myData;
	i32 mySize;
};

template <typename T>
Ref<List<T>> List<T>::operator=(RValue<List> aOther)
{
	myData = std::move(aOther.myData);
	mySize = aOther.mySize;
	aOther.mySize = 0;
	return *this;
}

// template <typename T>
// Ref<List<T>> List<T>::operator=(ConstRef<List> aOther)
// {
// 	return *this;
// }

template <typename T>
List<T>::List(RValue<List> aOther)
	: List()
{
	*this = std::move(aOther);
}

template <typename T>
List<T>::List(ConstRef<List> aOther)
{
	myData = ResizableArray<T>(aOther.myData);
	mySize = aOther.mySize;
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
	mySize = aLength;
}

template <typename T>
bool List<T>::Reserve(Const<i32> aLength, Const<bool> aClearMemory /*= true*/)
{
	if (aLength > Capacity())
	{
		myData.Resize(aLength, aClearMemory);
		return true;
	}
	return false;
}

template <typename T>
List<T>::List(Const<i32> aLength, Const<bool> aClearMemory /*= true*/)
	: myData(aLength, aClearMemory)
{
	mySize = 0;
}

template <typename T>
void List<T>::RemoveAtIndex(Const<i32> aIndex)
{
#ifdef _DEBUG
	if (mySize <= 0)
		abort();
#endif

	for (size i = aIndex + 1; i < mySize; ++i)
		std::move(myData[i], myData[i - 1]);
	
	--mySize;

	new (&myData[mySize]) T();
}

template <typename T>
void List<T>::Clear()
{
	myData.Reset();
	mySize = 0;
}

template <typename T>
void List<T>::Add(ConstRef<T> aItem)
{
	mySize++;
	if (mySize >= Capacity())
		Reserve(Max(8, Capacity() * 2));
	myData[mySize - 1] = aItem;
}

template <typename T>
void List<T>::Add(RValue<T> aItem)
{
	mySize++;
	if (mySize >= Capacity())
		Reserve(Max(8, Capacity() * 2));
	myData[mySize - 1] = std::move(aItem);
}

template <typename T>
List<T>::List()
{
	mySize = 0;
}

template <typename T>
List<T>::~List()
{
	for (i32 i = 0; i < Size(); ++i)
		myData[i].~T();
	mySize = 0;
}

template <typename T>
i32 List<T>::Size() const
{
	return mySize;
}

template <typename T>
i32 List<T>::Capacity() const
{
	return static_cast<i32>(myData.Size());
}

template <typename T>
void List<T>::SetLength(Const<i32> aLength)
{
#ifdef _DEBUG
	if (aLength < 0 || aLength > Capacity())
		abort();
#endif

	mySize = aLength;
}
