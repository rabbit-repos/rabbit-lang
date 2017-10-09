#pragma once
#include "Array.h"

template <typename TType, typename TCharacterMapper>
class StringMap
{
public:
	StringMap();
	StringMap(RValue<StringMap> aOther);
	StringMap(ConstRef<StringMap> aOther);
	virtual ~StringMap();

	Ref<StringMap> operator=(ConstRef<StringMap> aOther);
	Ref<StringMap> operator=(RValue<StringMap> aOther);

	Ptr<TType> TryGetValue(ConstRef<String> aString);
	ConstPtr<TType> TryGetValue(ConstRef<String> aString) const;

	Ref<TType> GetOrCreateValue(ConstRef<String> aString);
	Ref<TType> operator[](String aString);

	// TODO: RemoveValue which deletes empty branches
	// void RemoveValue(String aString);

private:
	TType myValue;
	Ptr<Array<TCharacterMapper::ArrayLength, ArraySize>> myNextLayer;
};

template <typename TType, typename TCharacterMapper>
StringMap<TType>::StringMap()
	: myValue()
{
	myNextLayer = null;
}

template <typename TType, typename TCharacterMapper>
StringMap<TType, TCharacterMapper>::StringMap(ConstRef<StringMap> aOther)
	: myValue(), myNextLayer(null)
{
	*this = aOther;
}

template <typename TType, typename TCharacterMapper>
StringMap<TType, TCharacterMapper>::StringMap(RValue<StringMap> aOther)
	: myValue(), myNextLayer(null)
{
	*this = std::move(aOther);
}

template <typename TType, typename TCharacterMapper>
Ref<StringMap<TType, TCharacterMapper>> StringMap<TType, TCharacterMapper>::operator=(ConstRef<SymbolFilter> aOther)
{
	delete myNextLayer;

	if (aOther.myNextLayer)
		myNextLayer = new SymbolFilter(*aOther.myNextLayer);
	else
		myNextLayer = null;

	myValue = aOther.myValue;

	return *this;
}

template <typename TType, typename TCharacterMapper>
Ref<StringMap<TType, TCharacterMapper>> StringMap<TType, TCharacterMapper>::operator=(RValue<StringMap<TType, TCharacterMapper>> aOther)
{
	delete myNextLayer;

	myNextLayer = std::move(aOther.myNextLayer);
	aOther.myNextLayer = null;

	myValue = std::move(aOther.myValue);
	aOther.myValue = TType();

	return *this;
}

template <typename TType, typename TCharacterMapper>
Ptr<TType> StringMap<TType, TCharacterMapper>::TryGetValue(String aString)
{
	// Should this even be considered a bad practice? (probably... ): ) 
	// return const_cast<Ptr<TType>>(static_cast<ConstPtr<SymbolFilter>>(this)->TryGetValue(aString));

	Ptr<StringMap> current = this;
	bool isFirstCharacter = true;
	for (;;)
	{
		// If we've reached the end of the string we're at the value we're looking for
		if (aString.Size() == 0)
			return current->myValue;

		if (!current->myNextLayer)
			return nullptr;

		Const<u8> mappedCharacter = Map(aString[0], isFirstCharacter);
		aString = aString.ChopRight(1);

		current = &(*current->myNextLayer)[mappedCharacter];
		isFirstCharacter = false;
	}
}

template <typename TType, typename TCharacterMapper>
ConstPtr<TType> StringMap<TType, TCharacterMapper>::TryGetValue(String aString) const
{
	ConstPtr<StringMap> current = this;
	bool isFirstCharacter = true;
	for (;;)
	{
		// If we've reached the end of the string we're at the value we're looking for
		if (aString.Size() == 0)
			return current->myValue;

		if (!current->myNextLayer)
			return nullptr;

		Const<u8> mappedCharacter = Map(aString[0], isFirstCharacter);
		aString = aString.ChopRight(1);

		current = &(*current->myNextLayer)[mappedCharacter];
		isFirstCharacter = false;
	}
}

template <typename TType, typename TCharacterMapper>
Ref<TType> StringMap<TType, TCharacterMapper>::operator[](String aString)
{
	return GetOrCreateValue(aString);
}

template <typename TType, typename TCharacterMapper>
Ref<TType> StringMap<TType, TCharacterMapper>::GetOrCreateValue(ConstRef<String> aString)
{
	Ptr<StringMap> current = this;
	bool isFirstCharacter = true;
	for (;;)
	{
		// If we've reached the end of the string we're at the value we're looking for
		if (aString.Size() == 0)
			return current->myValue;

		if (!current->myNextLayer)
		{
			current->myNextLayer = new Array<SymbolFilter, ArraySize>();

			// TODO: Look into, can probably only happen will malloc, new probably throws
			if (!current->myNextLayer)
				abort();
		}

		Const<u8> mappedCharacter = Map(aString[0], isFirstCharacter);
		aString = aString.ChopRight(1);
		
		current = &(*current->myNextLayer)[mappedCharacter];
		isFirstCharacter = false;
	}
}

template <typename TType, typename TCharacterMapper>
StringMap<TType, TCharacterMapper>::~StringMap()
{
	delete myNextLayer;
#ifdef _DEBUG
	myNextLayer = null;
#endif
}
