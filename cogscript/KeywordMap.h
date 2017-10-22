#pragma once
#include "StringMap.h"
#include "CharUtility.h"
#include "VirtualList.h"
#include "KeywordID.h"

class KeywordMapIndices
{
public:
	static constexpr u8 MinValue = static_cast<u8>(TokenID::AlphabetStart);
	static constexpr u8 MaxValue = static_cast<u8>(TokenID::AlphabetEnd);
	static constexpr u8 ArraySize = MaxValue - MinValue + 1;
};

class KeywordMap final : public StringMap<KeywordMap, KeywordID, KeywordMapIndices::ArraySize>
{
	using Super = StringMap<KeywordMap, KeywordID, KeywordMapIndices::ArraySize>;

public:
	KeywordMap();
	KeywordMap(RValue<KeywordMap> aMove);
	Ref<KeywordMap> operator=(RValue<KeywordMap> aMove);
	~KeywordMap();

	// Use Copy() insted
	KeywordMap(ConstRef<KeywordMap>) = delete;
	// Use Copy() insted
	Ref<KeywordMap> operator=(ConstRef<KeywordMap>) = delete;

	void AddKeyword(ConstRef<String> aString, Const<KeywordID> aKeyword);

protected:
	i32 Map(Const<Char> aCharacter, Const<i32> aIndex) const override;
};
