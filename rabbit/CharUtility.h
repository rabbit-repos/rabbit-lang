#pragma once

enum class LexemeID : u8;

class CharUtility
{
public:
	static bool IsWhiteSpace(Const<Char> aChar);
	
	static LexemeID GetDigitLexemeID(Const<Char> aChar, Const<bool> aIsFirstCharacter);
	static bool IsDigit(Const<Char> aChar);
	
	static bool IsControl(Const<Char> aChar);
	
	static bool IsLetter(Const<Char> aChar);
	static LexemeID GetLetterLexemeID(Const<Char> aChar);

	static bool IsValidLexemeCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter);
	static LexemeID GetLexemeIDFromCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter);

	static Char ToLower(Const<Char> aChar);
	static Char ToUpper(Const<Char> aChar);

	static constexpr Char FirstUpperCaseLetter = L'A';
	static constexpr Char LastUpperCaseLetter = L'Z';
	static constexpr Char FirstLowerCaseLetter = L'a';
	static constexpr Char LastLowerCaseLetter = L'z';

private:
	CharUtility() { }
};

enum class LexemeIDRanges : u8
{
	FirstLetter = 1,
	LastLetter = FirstLetter + ('Z' - 'A') + ('z' - 'a') + 1,
	FirstDigit = LastLetter + 1,
	LastDigit = FirstDigit + 9
};

enum class LexemeID : u8
{
	None,
	FirstValid,
	// 1 - XXX is the alphabet
	Alphabet = FirstValid,
	// XXX - XXX is the digits
	Digits = static_cast<u8>(LexemeIDRanges::FirstDigit),

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

	Count,
};
