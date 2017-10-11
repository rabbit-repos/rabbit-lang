#pragma once
#include "StringMap.h"
#include "CharUtility.h"

class SpecialTokenMapData
{
public:
	static constexpr u8 MinValue = static_cast<u8>(TokenID::FirstValid);
	static constexpr u8 MaxValue = static_cast<u8>(TokenID::Count);
	static constexpr u8 ArraySize = MaxValue - MinValue + 1;
};

template <typename T>
class SpecialTokenMap;

template <typename T>
class SpecialTokenMap : public StringMap<SpecialTokenMap<T>, T, SpecialTokenMapData::ArraySize>
{
protected:
	i32 Map(Const<Char> aCharacter) const final;
};

template <typename T>
i32 SpecialTokenMap<T>::Map(Const<Char> aCharacter) const
{
	static_assert(sizeof TokenID <= sizeof i32, "TokenID must fit in an i32");
	return static_cast<u8>(CharUtility::GetTokenIDFromCharacter(aCharacter, true));
}
