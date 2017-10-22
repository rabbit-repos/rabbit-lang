#include "pch.h"
#include "Token.h"

Token::Token(Const<TokenID> aTokenID, ConstRef<TokenContext> aContext)
{
	myTokenID = aTokenID;
	myContext = aContext; 
}

Token::Token(RValue<Token> aToken)
{
	*this = std::move(aToken);
}

Token::Token(ConstRef<Token> aToken)
{
	myTokenID = aToken.myTokenID;
	myContext = aToken.GetContext();
}

Token::~Token()
{
}

Ref<Token> Token::operator=(RValue<Token> aToken)
{
	myTokenID = std::move(aToken.myTokenID);
	myContext = std::move(aToken.myContext);
	return *this;
}

TokenID Token::GetTokenID() const
{
	return myTokenID;
}

Ref<TokenContext> Token::GetContext()
{
	return myContext;
}

ConstRef<TokenContext> Token::GetContext() const
{
	return myContext;
}


ConstRef<String> Token::GetContextData() const
{
	return myContext.GetData();
}

Token Token::Copy() const
{
	return Token(myTokenID, myContext);
}


String Token::TypeToString() const
{
	switch (myTokenID)
	{
		return L"None";
	case TokenID::AlphabetStart:
		return L"Alphabet";
	case TokenID::Digits:
		return L"Digits";
	case TokenID::Underscore:
		return L"Underscore";
	case TokenID::CompilerDirective:
		return L"CompilerDirective";
	case TokenID::OpeningAngleBracket:
		return L"OpeningAngleBracket";
	case TokenID::ClosingAngleBracket:
		return L"ClosingAngleBracket";
	case TokenID::OpeningSquareBracket:
		return L"OpeningSquareBracket";
	case TokenID::ClosingSquareBracket:
		return L"ClosingSquareBracket";
	case TokenID::Ampersand:
		return L"gAmpersand";
	case TokenID::Modulus:
		return L"Modulus";
	case TokenID::Plus:
		return L"Plus";
	case TokenID::Hyphen:
		return L"Hyphen";
	case TokenID::Asterisk:
		return L"Asterisk";
	case TokenID::Caret:
		return L"Caret";
	case TokenID::SemiColon:
		return L"Semicolon";
	case TokenID::Colon:
		return L"Colon";
	case TokenID::EqualitySign:
		return L"EqualitySign";
	case TokenID::Exclamation:
		return L"Exclamation";
	case TokenID::Tilde:
		return L"Tildle";
	case TokenID::OpeningCurlyBrace:
		return L"OpeningCurlyBrace";
	case TokenID::ClosingCurlyBrace:
		return L"ClosingCurlyBrace";
	case TokenID::OpeningParenthesis:
		return L"OpeningParenthesis";
	case TokenID::ClosingParenthesis:
		return L"ClosingParenthesis";
	case TokenID::Comma:
		return L"Comma";
	case TokenID::VerticalBar:
		return L"VerticalBar";
	case TokenID::Quote:
		return L"Quote";
	case TokenID::DollarSign:
		return L"DollarSign";
	case TokenID::AtSign:
		return L"AtSign";
	case TokenID::EuroSign:
		return L"EuroSign";
	case TokenID::PundSign:
		return L"PoundSign";
	case TokenID::Dot:
		return L"Dot";
	case TokenID::ScopeOperator:
		return L"ScopeOperator";
	case TokenID::Incrementation:
		return L"Incrementation";
	case TokenID::Decrementation:
		return L"Decrementation";
	case TokenID::BitShiftLeft:
		return L"BitShitLeft";
	case TokenID::BitShiftRight:
		return L"BitShiftRight";
	case TokenID::NumberLiteral:
		return L"NumberLiteral";
	case TokenID::StringLiteral:
		return L"StringLiteral";
	case TokenID::Text:
		return L"Text";
	case TokenID::QuestionMark:
		return L"QuestionMark";
	case TokenID::Count:
	case TokenID::Invalid:
	default:
		abort();
	}
}

void Token::AddError(Const<ErrorCode::Type> aErrorCode, ConstRef<String> aErrorMessage)
{
	myErrorList.Add(AppendString(ErrorCode::ToString(aErrorCode), L": ", aErrorMessage));
}

bool Token::operator==(Const<TokenID> aRight) const
{
	return myTokenID == aRight;
}

bool Token::operator!=(Const<TokenID> aRight) const
{
	return myTokenID != aRight;
}
