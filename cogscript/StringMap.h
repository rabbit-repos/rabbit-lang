#pragma once
#include "Array.h"

template <typename TImpl, typename TType, size TArrayLength>
class StringMap
{
protected:
	StringMap();

	virtual i32 Map(Const<Char> aCharacter) const = 0;

public:
	virtual ~StringMap();

	StringMap(RValue<StringMap> aOther);
	Ref<StringMap> operator=(RValue<StringMap> aOther);

	// Use Copy() instead
	StringMap(ConstRef<StringMap> aOther) = delete;
	// Use Copy() instead
	Ref<StringMap> operator=(ConstRef<StringMap> aOther) = delete;

	// void CopyTo(Ref<StringMap> aTarget) const;

	Ptr<TType> TryGetValue(String aString);
	ConstPtr<TType> TryGetValue(String aString) const;

	Ref<TType> GetOrCreateValue(String aString);
	Ref<TType> operator[](String aString);

	Ref<TImpl> GetNextLayer(Const<Char> aCharacter);
	Ptr<TImpl> TryGetNextLayer(Const<Char> aCharacter) const;

	ConstRef<TType> GetOurValue() const;
	Ref<TType> GetOurValue();

	u16 GetDepth() const;

	// TODO: RemoveValue which deletes empty branches
	// void RemoveValue(String aString);

private:
	TType myValue;
	Ptr<Array<TImpl, TArrayLength>> myNextLayer;
	u16 myDepth;
};

template <typename TImpl, typename TType, size TArrayLength>
Ref<TImpl> StringMap<TImpl, TType, TArrayLength>::GetNextLayer(Const<Char> aCharacter)
{
	if (myNextLayer == null)
	{
		myNextLayer = new Array<TImpl, TArrayLength>();
		myDepth = 1;
	}
	return (*myNextLayer)[Map(aCharacter)];
}

template <typename TImpl, typename TType, size TArrayLength>
Ptr<TImpl> StringMap<TImpl, TType, TArrayLength>::TryGetNextLayer(Const<Char> aCharacter) const
{
	if (myNextLayer == null)
		return nullptr;
	return &(*myNextLayer)[Map(aCharacter)];
}

// INCOMPLETE
// template <typename TType, size TArrayLength>
// StringMap<TType, TArrayLength> StringMap<TType, TCharacterMapper>::CopyTo(Ref<StringMap> aTarget) const
// {
// 	StringMap copy;
// 
// 	if (myNextLayer)
// 	{
// 		copy.myNextLayer = new StringMap();
// 		myNextLayer->CopyTo(copy.myNextLayer);
// 	}
// 	else
// 		copy.myNextLayer = null;
// 
// 	copy.myValue = myValue;
// 	copy.myDepth = myDepth;
// 
// 	return *this;
// }

template <typename TImpl, typename TType, size TArrayLength>
StringMap<TImpl, TType, TArrayLength>::StringMap()
	: myValue()
{
	myDepth = 0;
	myNextLayer = null;
}

template <typename TImpl, typename TType, size TArrayLength>
StringMap<TImpl, TType, TArrayLength>::StringMap(RValue<StringMap> aOther)
	: myValue(), myNextLayer(null)
{
	*this = std::move(aOther);
}

template <typename TImpl, typename TType, size TArrayLength>
Ref<StringMap<TImpl, TType, TArrayLength>> StringMap<TImpl, TType, TArrayLength>::operator=(RValue<StringMap<TImpl, TType, TArrayLength>> aOther)
{
	delete myNextLayer;

	myNextLayer = std::move(aOther.myNextLayer);
	aOther.myNextLayer = null;

	myValue = std::move(aOther.myValue);
	aOther.myValue = TType();

	myDepth = std::move(aOther.myDepth);
	aOther.myDepth = 0;

	return *this;
}

template <typename TImpl, typename TType, size TArrayLength>
Ptr<TType> StringMap<TImpl, TType, TArrayLength>::TryGetValue(String aString)
{
	Ptr<StringMap> current = this;
	for (;;)
	{
		// If we've reached the end of the string we're at the value we're looking for
		if (aString.Size() == 0)
			return current->myValue;

		if (!current->myNextLayer)
			return nullptr;

		Const<i32> mappedCharacter = Map(aString[0]);
		aString = aString.ChopRight(1);

		current = &(*current->myNextLayer)[mappedCharacter];
	}
}

template <typename TImpl, typename TType, size TArrayLength>
ConstPtr<TType> StringMap<TImpl, TType, TArrayLength>::TryGetValue(String aString) const
{
	ConstPtr<StringMap> current = this;
	for (;;)
	{
		// If we've reached the end of the string we're at the value we're looking for
		if (aString.Size() == 0)
			return current->myValue;

		if (!current->myNextLayer)
			return nullptr;

		Const<i32> mappedCharacter = Map(aString[0]);
		aString = aString.ChopRight(1);

		current = &(*current->myNextLayer)[mappedCharacter];
	}
}

template <typename TImpl, typename TType, size TArrayLength>
Ref<TType> StringMap<TImpl, TType, TArrayLength>::operator[](String aString)
{
	return GetOrCreateValue(aString);
}

template <typename TImpl, typename TType, size TArrayLength>
Ref<TType> StringMap<TImpl, TType, TArrayLength>::GetOrCreateValue(String aString)
{
	Ptr<StringMap> current = this;
	for (;;)
	{
		// If we've reached the end of the string we're at the value we're looking for
		if (aString.Size() == 0)
			return current->myValue;

		if (!current->myNextLayer)
		{
			current->myNextLayer = new Array<TImpl, TArrayLength>();

			// TODO: Look into, can probably only happen will malloc, new probably throws
			if (!current->myNextLayer)
				abort();

			myDepth++;
		}

		Const<i32> mappedCharacter = Map(aString[0]);
		aString = aString.ChopRight(1);
		
		current = &(*current->myNextLayer)[mappedCharacter];
	}
}


template <typename TImpl, typename TType, size TArrayLength>
Ref<TType> StringMap<TImpl, TType, TArrayLength>::GetOurValue()
{
	return myValue;
}

template <typename TImpl, typename TType, size TArrayLength>
ConstRef<TType> StringMap<TImpl, TType, TArrayLength>::GetOurValue() const
{
	return myValue;
}

template <typename TImpl, typename TType, size TArrayLength>
u16 StringMap<TImpl, TType, TArrayLength>::GetDepth() const
{
	return myDepth;
}

template <typename TImpl, typename TType, size TArrayLength>
StringMap<TImpl, TType, TArrayLength>::~StringMap()
{
	delete myNextLayer;
#ifdef _DEBUG
	myNextLayer = null;
#endif
}
