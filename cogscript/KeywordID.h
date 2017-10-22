#pragma once

enum class KeywordID : u8
{
	Unknown,
	Type,
	Global,
	Event,
	Inherits,
	Requires,
	End,
	Function,
	Internal,
	Return,
	Returns,
	Alias,
	Static,
	FlowControl,
	SkipWhen,
	RepeatWhen,
	Mixin,
	Mutable,
	Const,
	Pure,
	Object,

	Last
};
