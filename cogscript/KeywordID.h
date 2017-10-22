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
	Mutable,
	Static,
	FlowControl,
	SkipWhen,
	RepeatWhen,
	Mixin
};
