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

SymbolID CharUtility::GetDigitSymbolID(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	if (!aIsFirstCharacter && static_cast<u8>(aChar) >= static_cast<u8>(SymbolIDValues::FirstDigit) && static_cast<u8>(aChar) <= static_cast<u8>(SymbolIDValues::LastDigit))
		return static_cast<SymbolID>(static_cast<u8>(SymbolIDValues::FirstDigit) + (aChar - L'0'));
	return SymbolID::None;
}

bool CharUtility::IsDigit(Const<Char> aChar)
{
	return aChar >= L'0' && aChar <= L'9';
}

bool CharUtility::IsSymbolCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	return GetCharacterSymbolID(aChar, aIsFirstCharacter) >= SymbolID::None;
}

SymbolID CharUtility::GetCharacterSymbolID(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	Const<SymbolID> letterID = GetLetterSymbolID(aChar);
	if (letterID > SymbolID::None)
		return letterID;

	Const<SymbolID> digitID = GetDigitSymbolID(aChar, aIsFirstCharacter);
	if (digitID > SymbolID::None)
		return digitID;
	
	switch (aChar)
	{
	case L'_':
		return SymbolID::Underscore;
	case L'-':
		return SymbolID::Hyphen;
	}

	return SymbolID::None;
}

bool CharUtility::IsControl(Const<Char> aChar)
{
	// TODO: Replace this std call
	return iswcntrl(aChar);
}

SymbolID CharUtility::GetLetterSymbolID(Const<Char> aChar)
{
	if (aChar >= FirstUpperCaseLetter && aChar <= LastUpperCaseLetter)
	{
		return static_cast<SymbolID>(aChar - FirstUpperCaseLetter);
	}
	if (aChar >= FirstLowerCaseLetter && aChar <= LastLowerCaseLetter)
	{
		return static_cast<SymbolID>((LastUpperCaseLetter - FirstUpperCaseLetter + 1) + aChar - FirstLowerCaseLetter);
	}
	return static_cast<SymbolID>(0);
}

bool CharUtility::IsLetter(Const<Char> aChar)
{
	return GetLetterSymbolID(aChar) > SymbolID::None;
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
