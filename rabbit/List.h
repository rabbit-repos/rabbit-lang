#pragma once
#include "ResizableArray.h"

template <typename T>
class List : public ResizableArray<T>
{
public:
	List();
	~List();

	size Length() const;
	size Capacity() const;

private:
	size myNumItems;
};

template <typename T>
List<T>::List()
{
	myNumItems = 0;
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
