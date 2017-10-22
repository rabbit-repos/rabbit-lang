#include "pch.h"
#include "Symbol.h"

Symbol::Symbol(String aIdentifier)
{
	myIdentifier = std::move(aIdentifier);
}

Symbol::~Symbol()
{
}
