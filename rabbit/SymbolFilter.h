#pragma once
#include "CharUtility.h"
#include "Array.h"

template <typename TType>
class SymbolFilter
{
public:
	SymbolFilter();
	~SymbolFilter();

	Ptr<TType> TryGetValue(String aString);
	ConstPtr<TType> TryGetValue(String aString) const;

	Ref<TType> GetOrCreateValue(String aString);
	Ref<TType> operator[](String aString);

	// TODO: RemoveValue which deletes empty branches
	// void RemoveValue(String aString);

private:
	static u8 Map(Const<Char> aChar, Const<bool> aIsFirstCharacter);
	
	static constexpr u8 MinValue = static_cast<u8>(SymbolID::FirstValid);
	static constexpr u8 MaxValue = static_cast<u8>(SymbolID::Count);
	static constexpr u8 ArraySize = MaxValue - MinValue + 1;

	TType myValue;
	Ptr<Array<SymbolFilter, ArraySize>> myNextLayer;
};

template <typename TType>
Ptr<TType> SymbolFilter<TType>::TryGetValue(String aString)
{
	// Should this even be considered a bad practice? (probably... ): ) 
	// return const_cast<Ptr<TType>>(static_cast<ConstPtr<SymbolFilter>>(this)->TryGetValue(aString));

	Ptr<SymbolFilter> current = this;
	bool isFirstCharacter = true;
	for (;;)
	{
		// If we've reached the end of the string we're at the value we're looking for
		if (aString.Length() == 0)
			return current->myValue;

		if (!current->myNextLayer)
			return nullptr;

		Const<u8> mappedCharacter = Map(aString[0], isFirstCharacter);
		aString = aString.ChopRight(1);

		current = (*current->myNextLayer)[mappedCharacter];
		isFirstCharacter = false;
	}
}

template <typename TType>
ConstPtr<TType> SymbolFilter<TType>::TryGetValue(String aString) const
{
	ConstPtr<SymbolFilter> current = this;
	bool isFirstCharacter = true;
	for (;;)
	{
		// If we've reached the end of the string we're at the value we're looking for
		if (aString.Length() == 0)
			return current->myValue;

		if (!current->myNextLayer)
			return nullptr;

		Const<u8> mappedCharacter = Map(aString[0], isFirstCharacter);
		aString = aString.ChopRight(1);

		current = (*current->myNextLayer)[mappedCharacter];
		isFirstCharacter = false;
	}
}

template <typename TType>
Ref<TType> SymbolFilter<TType>::operator[](String aString)
{
	return GetOrCreateValue(aString);
}

template <typename TType>
Ref<TType> SymbolFilter<TType>::GetOrCreateValue(String aString)
{
	Ptr<SymbolFilter> current = this;
	bool isFirstCharacter = true;
	for (;;)
	{
		// If we've reached the end of the string we're at the value we're looking for
		if (aString.Length() == 0)
			return current->myValue;

		if (!current->myNextLayer)
		{
			current->myNextLayer = new Array<SymbolFilter, ArraySize>();

			// TODO: Look into, can probably only happen will malloc
			if (!current->myNextLayer)
				abort();
		}

		Const<u8> mappedCharacter = Map(aString[0], isFirstCharacter);
		aString = aString.ChopRight(1);
		
		current = &(*current->myNextLayer)[mappedCharacter];
		isFirstCharacter = false;
	}
}

template <typename TType>
SymbolFilter<TType>::SymbolFilter()
	: myValue()
{
	myNextLayer = null;
}

template <typename TType>
SymbolFilter<TType>::~SymbolFilter()
{
	delete myNextLayer;
}

template <typename TType>
u8 SymbolFilter<TType>::Map(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	static_assert(ArraySize <= MaxValue, "SymbolFilter only works on u8s");
	Const<SymbolID> mappedValue = CharUtility::GetCharacterSymbolID(aChar, aIsFirstCharacter);
	if (mappedValue == SymbolID::None)
	{
#ifdef _DEBUG
		std::cout << "This value was not able to be mapped to a symbol" << std::endl;
#endif
		abort();
	}
	return static_cast<u8>(mappedValue);
}
