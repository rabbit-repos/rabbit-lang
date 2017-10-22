#include "pch.h"
#include "ErrorCode.h"

String ErrorCode::ToString(Const<Type> aErrorCode)
{
	static_assert(ErrorCode::Count == 1, "New ErrorCode added; please add it to the To String method.");

	switch (aErrorCode)
	{
	case UnexpectedKeyword:
		return L"Unexpected Keyword";

	default:
#ifdef _DEBUG
		abort();
#else
		return L"Unknown";
#endif
	}
}

String ErrorCode::GetDefaultMessage(Const<Type> aErrorCode)
{
	static_assert(ErrorCode::Count == 1, "New ErrorCode added; please add Default Error Message.");

	switch (aErrorCode)
	{
	case UnexpectedKeyword:
		return L"This keyword was not expected at this location.";

	default:
#ifdef _DEBUG
		abort();
#else
		return L"";
#endif
	}
}
