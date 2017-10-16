#include "pch.h"
#include "TokenContext.h"

TokenContext::TokenContext()
{
}

TokenContext::TokenContext(String aData)
{
	myData = std::move(aData);
}

TokenContext::~TokenContext()
{
}

ConstRef<String> TokenContext::GetData() const
{
	return myData;
}
