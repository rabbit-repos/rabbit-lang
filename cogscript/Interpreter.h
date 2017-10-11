#pragma once

enum class ErrorType
{
	CompilerNotImplemented,

	Count
};

class CodeTokens;

struct InterpretationResult
{
	StringData ErrorMessage;
	ErrorType ErrorType;
	class CodeTree * InterpretedTree;
};

class Transpiler
{
public:
	Transpiler(ConstRef<class Config> aConfiguration);
	~Transpiler();

	InterpretationResult Interpret(ConstRef<CodeTokens> aCodeTokens) const;

private:
	ConstPtr<class Config> myConfig;
};
