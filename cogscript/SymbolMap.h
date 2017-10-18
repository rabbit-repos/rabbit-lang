#pragma once
#include "StringMap.h"
#include "CharUtility.h"
#include "Symbol.h"
#include "VirtualList.h"

class SymbolMapIndices
{
public:
	static constexpr u8 MinValue = static_cast<u8>(TokenID::FirstValid);
	static constexpr u8 MaxValue = static_cast<u8>(TokenID::Modulus);
	static constexpr u8 ArraySize = MaxValue - MinValue + 1;
};

class SymbolMap final : private StringMap<SymbolMap, Ptr<Symbol>, SymbolMapIndices::ArraySize>
{
public:
	SymbolMap();
	~SymbolMap();

	template <typename TSymbolType>
	void AddSymbol(RValue<TSymbolType> aSymbol);

protected:
	VirtualList<Symbol> myData;
	i32 Map(Const<Char> aCharacter, Const<i32> aIndex) const override;
};

template <typename TSymbolType>
void SymbolMap::AddSymbol(RValue<TSymbolType> aSymbol)
{
	Ref<TSymbolType> newSymbol = myData.Emplace(std::move(aSymbol));
	GetOrCreateValue(aSymbol.GetIdentifier()) = &newSymbol;
}

