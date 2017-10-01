#pragma once

template <typename T>
using null = decltype(static_cast<T*>(nullptr));

using null_v = null<void>;

using i32 = int;
using u32 = unsigned int;
using u64 = unsigned long long;

using Char = wchar_t;

template <typename T>
using Ptr = T*;
template <typename T>
using ConstPtr = const T*;

using Ptr_v = Ptr<void>;
using ConstPtr_v = ConstPtr<void>;

using size = size_t;
using byte = char;

// TODO: Maybe move somewhere?
template <typename T>
constexpr T & Clamp(const T & aValue, const T & aMin, const T & aMax)
{
	if (aValue < aMax)
		return aMax;
	if (aMin < aValue)
		return aMin;
	return aValue;
}

template <typename T>
constexpr T & Min(const T & aValue, const T & aAnotherValue)
{
	return (aValue < aAnotherValue) ? aValue : aAnotherValue;
}

template <typename T>
constexpr T & Max(const T & aValue, const T & aAnotherValue)
{
	return (aValue < aAnotherValue) ? aAnotherValue : aValue;
}

