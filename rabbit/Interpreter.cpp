#include "pch.h"
#include "Interpreter.h"
#include "Config.h"
#include "LexedCode.h"

Interpreter::Interpreter(ConstRef<Config> aConfiguration)
{
	myConfig = &aConfiguration;
}

Interpreter::~Interpreter()
{
}

InterpretationResult Interpreter::Interpret(ConstRef<LexedCode> aLexedCode) const
{
	(aLexedCode);

	InterpretationResult result;
	result.ErrorMessage = StringData(L"Compiler Not Implemented");
	result.ErrorType = ErrorType::CompilerNotImplemented;
	return result;
}
