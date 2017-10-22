#include "pch.h"
#include "ObjectSymbol.h"

ObjectSymbol::ObjectSymbol()
	: Symbol(L"ERROR")
{
}

ObjectSymbol::ObjectSymbol(String aIdentifier)
	: Symbol(std::move(aIdentifier))
{
}

ObjectSymbol::~ObjectSymbol()
{
}
