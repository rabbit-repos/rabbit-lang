#pragma once

enum class SymbolCharacterID : u8;

class CharUtility
{
public:
	static bool IsWhiteSpace(Const<Char> aChar);
	
	static SymbolCharacterID GetDigitLexemeID(Const<Char> aChar, Const<bool> aIsFirstCharacter);
	static bool IsDigit(Const<Char> aChar);
	
	static bool IsControl(Const<Char> aChar);
	
	static bool IsLetter(Const<Char> aChar);
	static SymbolCharacterID GetLetterSymbolCharacterID(Const<Char> aChar);

	static bool IsValidLexemeCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter);
	static SymbolCharacterID GetSymbolCharacterID(Const<Char> aChar, Const<bool> aIsFirstCharacter);

	static Char ToLower(Const<Char> aChar);
	static Char ToUpper(Const<Char> aChar);

	static constexpr Char FirstUpperCaseLetter = L'A';
	static constexpr Char LastUpperCaseLetter = L'Z';
	static constexpr Char FirstLowerCaseLetter = L'a';
	static constexpr Char LastLowerCaseLetter = L'z';

	enum class SymbolIDValues : u8
	{
		FirstLetter = 1,
		LastLetter = FirstLetter + ('Z' - 'A') + ('z' - 'a') + 1,
		FirstDigit = LastLetter + 1,
		LastDigit = FirstDigit + 9
	};

private:
	CharUtility() { }
};

enum class SymbolCharacterID : u8
{
	None,
	FirstValid,
	// 1 - XXX is the alphabet
	Alphabet = FirstValid,
	// XXX - XXX is the digits
	Digits = static_cast<u8>(CharUtility::SymbolIDValues::FirstDigit),
	Underscore = Digits + 10,
	Hyphen,

	Count
	// Space ??? TODO: Figure out if this is actually necessary/possibly etc.
};
