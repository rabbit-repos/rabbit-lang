#pragma once

enum class ErrorType
{
	CompilerNotImplemented,

	Count
};

class CodeTokens;
class TranspilerContext;

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
	void ParseGlobalScope(ConstRef<TranspilerContext> aContext) const;
};
