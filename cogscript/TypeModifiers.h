#pragma once

enum class TypeModifiers : u8
{
	None = 0,
	Global = 1 << 0,
	Internal = 1 << 1
	// NotUsed = 1 << 2,
	// NotUsed = 1 << 3,
	// NotUsed = 1 << 4,
	// NotUsed = 1 << 5,
	// NotUsed = 1 << 6,
	// NotUsed = 1 << 7
};
