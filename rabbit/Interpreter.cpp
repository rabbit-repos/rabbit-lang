#include "pch.h"
#include "Interpreter.h"
#include "Config.h"
#include "CodeTokens.h"

Interpreter::Interpreter(ConstRef<Config> aConfiguration)
{
	myConfig = &aConfiguration;
}

Interpreter::~Interpreter()
{
}

InterpretationResult Interpreter::Interpret(ConstRef<CodeTokens> aCodeTokens) const
{
	(aCodeTokens);

	InterpretationResult result;
	result.ErrorMessage = StringData(L"Compiler Not Implemented");
	result.ErrorType = ErrorType::CompilerNotImplemented;
	return result;
}
