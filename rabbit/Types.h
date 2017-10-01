#pragma once

constexpr decltype(nullptr) null = nullptr;

using i8 = signed char;
using u8 = unsigned char;
using i16 = short;
using u16 = unsigned short;
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;

using Char = wchar_t;

// TODO: Replace these two with classes with null checking etc
template <typename T>
using Ptr = T*;
template <typename T>
using ConstPtr = const T*;

using Ptr_v = Ptr<void>;
using ConstPtr_v = ConstPtr<void>;

template <typename T>
using Const = const T;

template <typename T>
using Ref = T&;
template <typename T>
using ConstRef = const T&;
template <typename T>
using RValue = T&&;

template <typename T>
using Out = Ref<T>;

using size = size_t;
using byte = char;

// TODO: Maybe move somewhere?
template <typename T>
constexpr const T & Clamp(const T & aValue, const T & aMin, const T & aMax)
{
	if (aValue < aMax)
		return aMax;
	if (aMin < aValue)
		return aMin;
	return aValue;
}

template <typename T>
constexpr const T & Min(const T & aValue, const T & aAnotherValue)
{
	return (aValue < aAnotherValue) ? aValue : aAnotherValue;
}

template <typename T>
constexpr const T & Max(const T & aValue, const T & aAnotherValue)
{
	return (aValue < aAnotherValue) ? aAnotherValue : aValue;
}

