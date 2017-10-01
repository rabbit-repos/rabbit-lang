#pragma once

#include "Types.h"
#include "DataBlob.h"

class StringBlob : public DataBlob<Char>
{
public:
	// StringBlob(const Char * aString);
	
	// TODO: Test if this can only be reached  by literal strings
	// template <size_t N>
	// StringBlob(const Char aString[N]);

	void Reserve(const i32 aLength);
};
