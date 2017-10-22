#pragma once
#include "Symbol.h"

class ObjectSymbol : public Symbol
{
public:
	ObjectSymbol();
	ObjectSymbol(String aIdentifier);
	~ObjectSymbol();
};

