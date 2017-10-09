#pragma once
#include "StringMap.h"
#include "CharUtility.h"

class Symbol {};

class SymbolMapper
{
public:
	static u8 Map(Const<Char> aChar, Const<bool> aIsFirstCharacter);

	static constexpr u8 MinValue = static_cast<u8>(TokenID::FirstValid);
	static constexpr u8 MaxValue = static_cast<u8>(TokenID::Count);
	static constexpr u8 ArraySize = MaxValue - MinValue + 1;
};

class SymbolMap : public StringMap<Symbol, SymbolMapper>
{
public:
	SymbolMap();
	~SymbolMap();
};

