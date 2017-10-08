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

LexemeID CharUtility::GetDigitLexemeID(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	if (!aIsFirstCharacter && IsDigit(aChar))
		return static_cast<LexemeID>(static_cast<u8>(LexemeIDRanges::FirstDigit) + (aChar - L'0'));
	return LexemeID::None;
}

bool CharUtility::IsDigit(Const<Char> aChar)
{
	return aChar >= L'0' && aChar <= L'9';
}

bool CharUtility::IsValidLexemeCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	return GetLexemeIDFromCharacter(aChar, aIsFirstCharacter) > LexemeID::None;
}

LexemeID CharUtility::GetLexemeIDFromCharacter(Const<Char> aChar, Const<bool> aIsFirstCharacter)
{
	Const<LexemeID> letterID = GetLetterLexemeID(aChar);
	if (letterID > LexemeID::None)
		return letterID;

	Const<LexemeID> digitID = GetDigitLexemeID(aChar, aIsFirstCharacter);
	if (digitID > LexemeID::None)
		return digitID;
	
	switch (aChar)
	{
	case L'_':
		return LexemeID::Underscore;
	case L'-':
		return LexemeID::Hyphen;
	}

	if (aIsFirstCharacter)
	{
		switch (aChar)
		{
		case L'#':
			return LexemeID::CompilerDirective;
		case L'<':
			return LexemeID::OpeningAngleBracket;
		case L'>':
			return LexemeID::ClosingAngleBracket;
		case L'[':
			return LexemeID::OpeningSquareBracket;
		case L']':
			return LexemeID::ClosingSquareBracket;
		case L'&':
			return LexemeID::Ampersand;
		case L'|':
			return LexemeID::VerticalBar;
		case L'%':
			return LexemeID::Modulus;
		case L'+':
			return LexemeID::Plus;
		case L'-':
			return LexemeID::Hyphen;
		case L'*':
			return LexemeID::Asterisk;
		case L'^':
			return LexemeID::Caret;
		case L';':
			return LexemeID::SemiColon;
		case L':':
			return LexemeID::Colon;
		case L'?':
			return LexemeID::QuestionMark;
		case L'=':
			return LexemeID::EqualitySign;
		case L'!':
			return LexemeID::Exclamation;
		case L'~':
			return LexemeID::Tilde;
		case L'{':
			return LexemeID::OpeningCurlyBrace;
		case L'}':
			return LexemeID::ClosingCurlyBrace;
		case L'(':
			return LexemeID::OpeningParenthesis;
		case L')':
			return LexemeID::ClosingParenthesis;
		case L',':
			return LexemeID::Comma;
		case L'\"':
			return LexemeID::Quote;
		case L'$':
			return LexemeID::DollarSign;
		case L'@':
			return LexemeID::AtSign;
		case L'€':
			return LexemeID::EuroSign;
		case L'£':
			return LexemeID::PundSign;
		case L'.':
			return LexemeID::Dot;
		}
	}

	return LexemeID::None;
}

bool CharUtility::IsControl(Const<Char> aChar)
{
	// TODO: Replace this std call
	return iswcntrl(aChar);
}

LexemeID CharUtility::GetLetterLexemeID(Const<Char> aChar)
{
	if (aChar >= FirstUpperCaseLetter && aChar <= LastUpperCaseLetter)
	{
		return static_cast<LexemeID>(aChar - FirstUpperCaseLetter + 1);
	}
	if (aChar >= FirstLowerCaseLetter && aChar <= LastLowerCaseLetter)
	{
		return static_cast<LexemeID>((LastUpperCaseLetter - FirstUpperCaseLetter + 2) + aChar - FirstLowerCaseLetter);
	}
	return LexemeID::None;
}

bool CharUtility::IsLetter(Const<Char> aChar)
{
	return GetLetterLexemeID(aChar) > LexemeID::None;
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
