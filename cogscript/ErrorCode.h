#pragma once

namespace ErrorCode
{
	enum Type : u8
	{
		UnexpectedKeyword,

		Count
	};

	String ToString(Const<ErrorCode::Type> aErrorCode);
	String GetDefaultMessage(Const<ErrorCode::Type> aErrorCode);
}
