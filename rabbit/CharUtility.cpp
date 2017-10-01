#include "pch.h"
#include "CharUtility.h"
#include <cwctype>

bool CharUtility::IsWhiteSpace(const Char aChar)
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

bool CharUtility::IsDigit(const Char aChar)
{
	return aChar >= L'0' && aChar <= L'9';
}

bool CharUtility::IsControl(const Char aChar)
{
	// TODO: Replace this std call
	return iswcntrl(aChar);
}
