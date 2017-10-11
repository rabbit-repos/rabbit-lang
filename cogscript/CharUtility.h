#pragma once
#include "TokenID.h"

class CharUtility
{
public:
	static bool IsWhiteSpace(Const<Char> aChar);
	
	static TokenID GetDigitLexemeID(Const<Char> aChar, Const<bool> aIsFirstCharacter);
	static bool IsDigit(Const<Char> aChar);
	
	static bool IsControl(Const<Char> aChar);
	
	static bool IsLetter(Const<Char> aChar);
	static TokenID GetLetterLexemeID(Const<Char> aChar);

	static bool IsValidLexemeCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter);
	static TokenID GetTokenIDFromCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter);

	static bool IsValidFirstSymbolCharacter(Const<Char> aChar);

	static Char ToLower(Const<Char> aChar);
	static Char ToUpper(Const<Char> aChar);

	static constexpr Char FirstUpperCaseLetter = L'A';
	static constexpr Char LastUpperCaseLetter = L'Z';
	static constexpr Char FirstLowerCaseLetter = L'a';
	static constexpr Char LastLowerCaseLetter = L'z';

private:
	CharUtility() { }
};
