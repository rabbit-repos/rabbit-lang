#include "pch.h"
#include "SymbolMap.h"

SymbolMap::SymbolMap()
{
}


SymbolMap::~SymbolMap()
{
}

i32 SymbolMap::Map(Const<Char> aCharacter, Const<i32> aIndex) const
{
	Const<TokenID> mappedValue = CharUtility::GetTokenIDFromCharacter(aCharacter, aIndex);
	if (mappedValue == TokenID::Invalid)
	{
		// This value was not able to be mapped to a symbol
		abort();
	}
	return static_cast<u8>(mappedValue);
}
