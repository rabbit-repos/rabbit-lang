#pragma once

enum class TokenIDRanges : u8
{
	FirstLetter = 1,
	LastLetter = FirstLetter + ('Z' - 'A') + ('z' - 'a') + 1,
	FirstDigit = LastLetter + 1,
	LastDigit = FirstDigit + 9
};

enum class TokenID : u8
{
	None,
	FirstValid,
	// 1 - XXX is the alphabet
	Alphabet = FirstValid,
	// XXX - XXX is the digits
	Digits = static_cast<u8>(TokenIDRanges::FirstDigit),

	Underscore = Digits + 10,
	CompilerDirective,
	OpeningAngleBracket,
	ClosingAngleBracket,
	OpeningSquareBracket,
	ClosingSquareBracket,
	Ampersand,
	Modulus,
	Plus,
	Hyphen,
	Asterisk,
	Caret,
	SemiColon,
	Colon,
	QuestionMark,
	EqualitySign,
	Exclamation,
	Tilde,
	OpeningCurlyBrace,
	ClosingCurlyBrace,
	OpeningParenthesis,
	ClosingParenthesis,
	Comma,
	VerticalBar,
	Quote,
	DollarSign,
	AtSign,
	EuroSign,
	PundSign,
	Dot,
	ScopeOperator,
	Incrementation,
	Decrementation,
	// Same as Stream Out
	BitShiftLeft,
	// Same as BitShiftLeft
	StreamOutput = BitShiftLeft,
	// Same as Stream Out
	BitShiftRight,
	// Same as BitShiftRight
	StreamInput = BitShiftRight,
	NumberLiteral,
	StringLiteral,

	Count
};
