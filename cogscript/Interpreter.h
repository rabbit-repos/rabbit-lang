#pragma once
#include "ErrorCode.h"

class CodeTokens;
class InterpreterContext;

struct InterpretationResult
{
	List<StringData> Errors;
	List<StringData> Warnings;
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
	void ParseGlobalScope(Ref<InterpreterContext> aContext) const;
	void ParseExpression(Ref<InterpreterContext> aContext) const;
	void ParseTypeModifiers(Ref<InterpreterContext> aContext) const;
	void ParseObject(Ref<InterpreterContext> aContext) const;
};
