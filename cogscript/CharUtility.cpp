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

TokenID CharUtility::GetDigitLexemeID(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	if (!aIsFirstCharacter && IsDigit(aChar))
		return static_cast<TokenID>(static_cast<u8>(TokenIDRanges::FirstDigit) + (aChar - L'0'));
	return TokenID::None;
}

bool CharUtility::IsDigit(Const<Char> aChar)
{
	return aChar >= L'0' && aChar <= L'9';
}

bool CharUtility::IsValidLexemeCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	return GetTokenIDFromCharacter(aChar, aIsFirstCharacter) > TokenID::None;
}

TokenID CharUtility::GetTokenIDFromCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	Const<TokenID> letterID = GetLetterLexemeID(aChar);
	if (letterID > TokenID::None)
		return letterID;

	Const<TokenID> digitID = GetDigitLexemeID(aChar, aIsFirstCharacter);
	if (digitID > TokenID::None)
		return digitID;
	
	switch (aChar)
	{
	case L'_':
		return TokenID::Underscore;
	case L'-':
		return TokenID::Hyphen;
	}

	if (aIsFirstCharacter)
	{
		switch (aChar)
		{
		case L'#':
			return TokenID::CompilerDirective;
		case L'<':
			return TokenID::OpeningAngleBracket;
		case L'>':
			return TokenID::ClosingAngleBracket;
		case L'[':
			return TokenID::OpeningSquareBracket;
		case L']':
			return TokenID::ClosingSquareBracket;
		case L'&':
			return TokenID::Ampersand;
		case L'|':
			return TokenID::VerticalBar;
		case L'%':
			return TokenID::Modulus;
		case L'+':
			return TokenID::Plus;
		case L'-':
			return TokenID::Hyphen;
		case L'*':
			return TokenID::Asterisk;
		case L'^':
			return TokenID::Caret;
		case L';':
			return TokenID::SemiColon;
		case L':':
			return TokenID::Colon;
		case L'?':
			return TokenID::QuestionMark;
		case L'=':
			return TokenID::EqualitySign;
		case L'!':
			return TokenID::Exclamation;
		case L'~':
			return TokenID::Tilde;
		case L'{':
			return TokenID::OpeningCurlyBrace;
		case L'}':
			return TokenID::ClosingCurlyBrace;
		case L'(':
			return TokenID::OpeningParenthesis;
		case L')':
			return TokenID::ClosingParenthesis;
		case L',':
			return TokenID::Comma;
		case L'\"':
			return TokenID::Quote;
		case L'$':
			return TokenID::DollarSign;
		case L'@':
			return TokenID::AtSign;
		case L'€':
			return TokenID::EuroSign;
		case L'£':
			return TokenID::PundSign;
		case L'.':
			return TokenID::Dot;
		}
	}

	return TokenID::None;
}

bool CharUtility::IsValidFirstSymbolCharacter(Const<Char> aChar)
{
	return IsLetter(aChar) || aChar == L'_' || aChar == L'~';
}

bool CharUtility::IsControl(Const<Char> aChar)
{
	// TODO: Replace this std call
	return iswcntrl(aChar);
}

TokenID CharUtility::GetLetterLexemeID(Const<Char> aChar)
{
	if (aChar >= FirstUpperCaseLetter && aChar <= LastUpperCaseLetter)
	{
		return static_cast<TokenID>(aChar - FirstUpperCaseLetter + 1);
	}
	if (aChar >= FirstLowerCaseLetter && aChar <= LastLowerCaseLetter)
	{
		return static_cast<TokenID>((LastUpperCaseLetter - FirstUpperCaseLetter + 2) + aChar - FirstLowerCaseLetter);
	}
	return TokenID::None;
}

bool CharUtility::IsLetter(Const<Char> aChar)
{
	return GetLetterLexemeID(aChar) > TokenID::None;
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
