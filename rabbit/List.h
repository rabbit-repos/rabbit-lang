#pragma once
#include "ResizableArray.h"
#include <xutility>

template <typename T>
class List : public ResizableArray<T>
{
public:
	List();
	~List();

	void Add(const T & aItem);
	void RemoveAtIndex(const i32 aIndex);

	size Length() const;
	size Capacity() const;

private:
	// TODO: Store initial X items on "stack", like so:
	// Array<

	size myNumItems;
};

template <typename T>
void List<T>::RemoveAtIndex(const i32 aIndex)
{
#ifdef _DEBUG
	if (myNumItems <= 0)
		abort();
#endif

	for (size i = aIndex + 1; i < myNumItems; ++i)
		std::move((*this)[i], (*this)[i - 1]);

	--myNumItems;
}

template <typename T>
void List<T>::Add(const T & aItem)
{
	myNumItems++;
	if (myNumItems >= Capacity())
		Reserve(Capacity() * 2);
	(*this)[myNumItems - 1] = aItem;
}

template <typename T>
List<T>::List()
{
	myNumItems = 0;
	Reserve(16);
}

template <typename T>
List<T>::~List()
{
}

template <typename T>
size List<T>::Length() const
{
	return myNumItems;
}

template <typename T>
size List<T>::Capacity() const
{
	return ResizableArray<T>::Length();
}
