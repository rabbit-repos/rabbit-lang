#include "pch.h"
#include "CharUtility.h"
#include <cwctype>

bool CharUtility::IsWhiteSpace(Const<Char> aChar)
{
	switch (aChar)
	{
	case L' ':
	case L'\f':
	case L'\n':
	case L'\r':
	case L'\t':
	case L'\v':
		return true;
	}
	return false;
}

SymbolCharacterID CharUtility::GetDigitLexemeID(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	if (!aIsFirstCharacter && IsDigit(aChar))
		return static_cast<SymbolCharacterID>(static_cast<u8>(SymbolIDValues::FirstDigit) + (aChar - L'0'));
	return SymbolCharacterID::None;
}

bool CharUtility::IsDigit(Const<Char> aChar)
{
	return aChar >= L'0' && aChar <= L'9';
}

bool CharUtility::IsValidLexemeCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	return GetSymbolCharacterID(aChar, aIsFirstCharacter) > SymbolCharacterID::None;
}

SymbolCharacterID CharUtility::GetSymbolCharacterID(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	Const<SymbolCharacterID> letterID = GetLetterSymbolCharacterID(aChar);
	if (letterID > SymbolCharacterID::None)
		return letterID;

	Const<SymbolCharacterID> digitID = GetDigitLexemeID(aChar, aIsFirstCharacter);
	if (digitID > SymbolCharacterID::None)
		return digitID;
	
	switch (aChar)
	{
	case L'_':
		return SymbolCharacterID::Underscore;
	case L'-':
		return aIsFirstCharacter ? SymbolCharacterID::None : SymbolCharacterID::Hyphen;
	}

	return SymbolCharacterID::None;
}

bool CharUtility::IsControl(Const<Char> aChar)
{
	// TODO: Replace this std call
	return iswcntrl(aChar);
}

SymbolCharacterID CharUtility::GetLetterSymbolCharacterID(Const<Char> aChar)
{
	if (aChar >= FirstUpperCaseLetter && aChar <= LastUpperCaseLetter)
	{
		return static_cast<SymbolCharacterID>(aChar - FirstUpperCaseLetter + 1);
	}
	if (aChar >= FirstLowerCaseLetter && aChar <= LastLowerCaseLetter)
	{
		return static_cast<SymbolCharacterID>((LastUpperCaseLetter - FirstUpperCaseLetter + 2) + aChar - FirstLowerCaseLetter);
	}
	return static_cast<SymbolCharacterID>(0);
}

bool CharUtility::IsLetter(Const<Char> aChar)
{
	return GetLetterSymbolCharacterID(aChar) > SymbolCharacterID::None;
}

Char CharUtility::ToLower(Const<Char> aChar)
{
	if (aChar >= FirstUpperCaseLetter && aChar <= LastUpperCaseLetter)
		return FirstLowerCaseLetter + (aChar - FirstUpperCaseLetter);
	return aChar;
}

Char CharUtility::ToUpper(Const<Char> aChar)
{
	if (aChar >= FirstLowerCaseLetter && aChar <= LastLowerCaseLetter)
		return FirstUpperCaseLetter + (aChar - FirstLowerCaseLetter);
	return aChar;
}
