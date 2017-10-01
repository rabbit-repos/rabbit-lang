#pragma once
#include "Types.h"

class CharUtility
{
public:
	static bool IsWhiteSpace(const Char aChar);
	static bool IsDigit(const Char aChar);
	static bool IsControl(const Char aChar);

private:
	CharUtility() { }
};
