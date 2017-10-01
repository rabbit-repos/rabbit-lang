#pragma once
#include "StringData.h"

enum class ErrorType
{
	CompilerNotImplemented,

	Count
};

struct InterpretationResult
{
	StringData ErrorMessage;
	ErrorType ErrorType;
	class CodeTree * InterpretedTree;
};

class Interpreter
{
public:
	Interpreter(ConstRef<class Config> aConfiguration);
	~Interpreter();

	InterpretationResult Interpret(ConstRef<ResizableArray<class Lexeme*>> aLexedCode) const;

private:
	ConstPtr<class Config> myConfig;
};


