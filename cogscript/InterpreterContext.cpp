#include "pch.h"
#include "InterpreterContext.h"
#include "CodeTokens.h"
#include "VirtualList.h"
#include "KeywordID.h"
#include "KeywordMap.h"

static KeywordMap GetKeywords();
static Const<KeywordMap> gKeywords(GetKeywords());

InterpreterContext::InterpreterContext(ConstRef<CodeTokens> aCodeTokens)
{
	myTokens = &aCodeTokens;
	myCursor = 0;
}

InterpreterContext::~InterpreterContext()
{
}

Ref<Token> InterpreterContext::At(Const<i32> aOffset /*= 0*/)
{
	return *myTokens->GetTokens()[Clamp(myCursor + aOffset, 0, myTokens->GetTokens().Size() - 1)];
}

ConstRef<Token> InterpreterContext::At(Const<i32> aOffset /*=0*/) const
{
	return *myTokens->GetTokens()[Clamp(myCursor + aOffset, 0, myTokens->GetTokens().Size() - 1)];
}

KeywordID InterpreterContext::KeywordAt(Const<i32> aOffset /*= 0*/) const
{
	Const<ConstPtr<KeywordID>> keyword = gKeywords.TryGetValue(At(aOffset).GetContextData());
	if (keyword == null)
		return KeywordID::Unknown;
	return *keyword;
}

ConstRef<TokenContext> InterpreterContext::ContextAt(Const<i32> aOffset /*=0*/) const
{
	return At(aOffset).GetContext();
}
Ref<TokenContext> InterpreterContext::ContextAt(Const<i32> aOffset /*= 0*/)
{
	return At(aOffset).GetContext();
}

i32 InterpreterContext::GetCursorLocation() const
{
	return myCursor;
}

bool InterpreterContext::IsAtEnd() const
{
	return myCursor >= myTokens->GetTokens().Size();
}

Ref<Namespace> InterpreterContext::GetGlobalNamespace()
{
	return myGlobalNamepsace;
}

ConstRef<Namespace> InterpreterContext::GetGlobalNamespace() const
{
	return myGlobalNamepsace;
}

void InterpreterContext::ReportErrorWithDefaultMessage(Const<ErrorCode::Type> aError, Const<i32> aOffset)
{
	At(aOffset).AddError(aError, ErrorCode::GetDefaultMessage(aError));
}

void InterpreterContext::ReportError(Const<ErrorCode::Type> aError, ConstRef<String> aErrorDescription, Const<i32> aOffset)
{
	At(aOffset).AddError(aError, aErrorDescription);
}

KeywordMap GetKeywords()
{
	KeywordMap keywords;
	keywords[L"type"] = KeywordID::Type;
	keywords[L"global"] = KeywordID::Global;
	keywords[L"event"] = KeywordID::Event;
	keywords[L"inherits"] = KeywordID::Inherits;
	keywords[L"requires"] = KeywordID::Requires;
	keywords[L"end"] = KeywordID::End;
	keywords[L"function"] = KeywordID::Function;
	keywords[L"internal"] = KeywordID::Internal;
	keywords[L"return"] = KeywordID::Return;
	keywords[L"returns"] = KeywordID::Returns;
	keywords[L"alias"] = KeywordID::Alias;
	keywords[L"mutable"] = KeywordID::Mutable;
	keywords[L"static"] = KeywordID::Static;
	keywords[L"flow_control"] = KeywordID::FlowControl;
	keywords[L"skip_when"] = KeywordID::SkipWhen;
	keywords[L"repeat_when"] = KeywordID::RepeatWhen;
	keywords[L"mixin"] = KeywordID::Mixin;
	keywords[L"const"] = KeywordID::Const;
	keywords[L"pure"] = KeywordID::Pure;
	keywords[L"object"] = KeywordID::Object;

	static_assert(static_cast<i32>(KeywordID::Last) == 21, "You added something to the keyword enumeration, please add it here if necessary and update this static assert!");
	return keywords;
}
