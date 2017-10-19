#pragma once

enum class ErrorType
{
	CompilerNotImplemented,

	Count
};

class CodeTokens;
class InterpreterContext;

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

	InterpretationResult Interpret(ConstRef<CodeTokens> aCodeTokens) const;

private:
	ConstPtr<class Config> myConfig;
	void ParseGlobalScope(ConstRef<InterpreterContext> aContext) const;
};
