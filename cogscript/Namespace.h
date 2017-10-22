#pragma once
#include "StringMap.h"
#include "CharUtility.h"
#include "Symbol.h"
#include "VirtualList.h"

class NamespaceMapIndices
{
public:
	static constexpr u8 MinValue = static_cast<u8>(TokenID::AlphabetStart);
	static constexpr u8 MaxValue = static_cast<u8>(TokenID::Underscore);
	static constexpr u8 ArraySize = MaxValue - MinValue + 1;
};

class Namespace final : private StringMap<Namespace, Ptr<Symbol>, NamespaceMapIndices::ArraySize>
{
public:
	Namespace();
	~Namespace();

	template <typename TSymbolType>
	Ref<TSymbolType> AddSymbol(RValue<TSymbolType> aSymbol);
	
	template <typename TImpl, typename TType, size TArrayLength>
	friend class StringMap;

protected:
	VirtualList<Symbol> myData;
	i32 Map(Const<Char> aCharacter, Const<i32> aIndex) const override;
};

template <typename TSymbolType>
Ref<TSymbolType> Namespace::AddSymbol(RValue<TSymbolType> aSymbol)
{
	Ref<TSymbolType> newSymbol = myData.Add<TSymbolType>(std::move(aSymbol));
	GetOrCreateValue(aSymbol.GetIdentifier()) = &newSymbol;
	return newSymbol;
}

