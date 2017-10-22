#include "pch.h"
#include "Namespace.h"

Namespace::Namespace()
{
}


Namespace::~Namespace()
{
}

i32 Namespace::Map(Const<Char> aCharacter, Const<i32> aIndex) const
{
	Const<TokenID> mappedValue = CharUtility::GetTokenIDFromCharacter(aCharacter, aIndex);
	if (mappedValue == TokenID::Invalid)
	{
		// This value was not able to be mapped to a symbol
		abort();
	}
	return static_cast<u8>(mappedValue);
}
