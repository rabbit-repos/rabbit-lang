#pragma once

class CharUtility
{
public:
	static bool IsWhiteSpace(const Char aChar);
	static bool IsDigit(const Char aChar);
	static bool IsValidSymbolCharacter(const Char aChar, const bool aIsFirstCharacter);
	static bool IsControl(const Char aChar);
	
private:
	CharUtility() { }
};
