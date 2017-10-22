#include "pch.h"
#include "KeywordMap.h"

KeywordMap::KeywordMap()
{
}

KeywordMap::KeywordMap(RValue<KeywordMap> aMove)
	: Super(std::move(aMove))
{

}

KeywordMap::~KeywordMap()
{
}

i32 KeywordMap::Map(Const<Char> aCharacter, Const<i32> aIndex) const
{
	Const<TokenID> mappedValue = CharUtility::GetTokenIDFromCharacter(aCharacter, aIndex);
	if (mappedValue == TokenID::Invalid)
	{
		// This value was not able to be mapped to a symbol
		FatalError();
	}

	return static_cast<u8>(mappedValue);
}

void KeywordMap::AddKeyword(ConstRef<String> aString, Const<KeywordID> aKeyword)
{
	this->GetOrCreateValue(aString) = aKeyword;
}

Ref<KeywordMap> KeywordMap::operator=(RValue<KeywordMap> aMove)
{
	*static_cast<Ptr<Super>>(this) = std::move(aMove);
	return *this;
}
