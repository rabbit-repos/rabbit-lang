#include "pch.h"
#include "SymbolMap.h"


SymbolMap::SymbolMap()
{
}


SymbolMap::~SymbolMap()
{
}

u8 SymbolMapper::Map(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	static_assert(ArraySize <= MaxValue, "SymbolFilter only works on u8s");
	Const<TokenID> mappedValue = CharUtility::GetTokenIDFromCharacter(aChar, aIsFirstCharacter);
	if (mappedValue == TokenID::None)
	{
#ifdef _DEBUG
		std::cout << "This value was not able to be mapped to a symbol" << std::endl;
#endif
		abort();
	}
	return static_cast<u8>(mappedValue);
}
