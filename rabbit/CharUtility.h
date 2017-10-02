#pragma once

enum class SymbolID : u8
{
	None,
	FirstValid,
	// 1 - XXX is the alphabet
	Alphabet = FirstValid,
	// XXX - XXX is the digits
	Digits,
	Underscore,
	Hyphen,
	
	Count
	// Space ??? TODO: Figure out if this is actually necessary/possibly etc.
};

class CharUtility
{
public:
	static bool IsWhiteSpace(Const<Char> aChar);
	
	static SymbolID GetDigitSymbolID(Const<Char> aChar, Const<bool> aIsFirstCharacter);
	static bool IsDigit(Const<Char> aChar);
	
	static bool IsControl(Const<Char> aChar);
	
	static bool IsLetter(Const<Char> aChar);
	static SymbolID GetLetterSymbolID(Const<Char> aChar);

	static bool IsSymbolCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter);
	static SymbolID GetCharacterSymbolID(Const<Char> aChar, Const<bool> aIsFirstCharacter);

	static Char ToLower(Const<Char> aChar);
	static Char ToUpper(Const<Char> aChar);

	static constexpr Char FirstUpperCaseLetter = L'A';
	static constexpr Char LastUpperCaseLetter = L'Z';
	static constexpr Char FirstLowerCaseLetter = L'a';
	static constexpr Char LastLowerCaseLetter = L'z';

	enum class SymbolIDValues : u8
	{
		FirstLetter = 1,
		LastLetter = FirstLetter + ('Z' - 'A' + 1) + ('z' - 'a' + 1),
		FirstDigit = LastLetter + 1,
		LastDigit = FirstDigit + 9
	};

private:
	CharUtility() { }
};

// template<>
// constexpr CharUtility::LetterID MaxOf<CharUtility::LetterID> = MaxOf<u8>;
