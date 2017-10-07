#include "pch.h"
#include "Interpreter.h"
#include "Config.h"
#include "SymbolFilter.h"

Interpreter::Interpreter(ConstRef<Config> aConfiguration)
{
	myConfig = &aConfiguration;
}

Interpreter::~Interpreter()
{
}

InterpretationResult Interpreter::Interpret(ConstRef<ResizableArray<class Lexeme*>> aLexedCode) const
{
	(aLexedCode);

	InterpretationResult result;
	result.ErrorMessage = StringData(L"Compiler Not Implemented");
	return result;
}
