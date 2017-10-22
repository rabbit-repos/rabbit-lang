#pragma once

template <typename TEnum, typename TEnable = std::enable_if_t<std::is_enum_v<TEnum>>>
Ref<TEnum> operator|=(Ref<TEnum> aLeft, ConstRef<TEnum> aRight)
{
	aLeft = static_cast<TEnum>(static_cast<std::underlying_type_t<TEnum>>(aLeft) | static_cast<std::underlying_type_t<TEnum>>(aRight));
	return aLeft;
}

template <typename TEnum, typename TEnable = std::enable_if_t<std::is_enum_v<TEnum>>>
Ref<TEnum> operator&=(Ref<TEnum> aLeft, ConstRef<TEnum> aRight)
{
	aLeft = static_cast<TEnum>(static_cast<std::underlying_type_t<TEnum>>(aLeft) & static_cast<std::underlying_type_t<TEnum>>(aRight));
	return aLeft;
}

template <typename TEnum, typename TEnable = std::enable_if_t<std::is_enum_v<TEnum>>>
Ref<TEnum> operator^=(Ref<TEnum> aLeft, ConstRef<TEnum> aRight)
{
	aLeft = static_cast<TEnum>(static_cast<std::underlying_type_t<TEnum>>(aLeft) ^ static_cast<std::underlying_type_t<TEnum>>(aRight));
	return aLeft;
}

template <typename TEnum, typename TEnable = std::enable_if_t<std::is_enum_v<TEnum>>>
TEnum operator|(Const<TEnum> aLeft, Const<TEnum> aRight)
{
	return static_cast<TEnum>(static_cast<std::underlying_type_t<TEnum>>(aLeft) | static_cast<std::underlying_type_t<TEnum>>(aRight));
}

template <typename TEnum, typename TEnable = std::enable_if_t<std::is_enum_v<TEnum>>>
TEnum operator&(Const<TEnum> aLeft, Const<TEnum> aRight)
{
	return static_cast<TEnum>(static_cast<std::underlying_type_t<TEnum>>(aLeft) & static_cast<std::underlying_type_t<TEnum>>(aRight));
}

template <typename TEnum, typename TEnable = std::enable_if_t<std::is_enum_v<TEnum>>>
TEnum operator^(Const<TEnum> aLeft, Const<TEnum> aRight)
{
	return static_cast<TEnum>(static_cast<std::underlying_type_t<TEnum>>(aLeft) ^ static_cast<std::underlying_type_t<TEnum>>(aRight));
}

template <typename TEnum, typename TEnable = std::enable_if_t<std::is_enum_v<TEnum>>>
bool FlagIsSet(Const<TEnum> aValue, Const<TEnum> aFlag)
{
	return static_cast<std::underlying_type_t<TEnum>>(aValue & aFlag) > 0;
}

template <typename TEnum, typename TEnable = std::enable_if_t<std::is_enum_v<TEnum>>>
void SetFlag(Ref<TEnum> aValue, Const<TEnum> aFlag)
{
	aValue &= aFlag;
}
