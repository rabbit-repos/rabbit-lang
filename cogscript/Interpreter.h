#pragma once
#include "ErrorCode.h"

class CodeTokens;
class InterpreterContext;
class ObjectSymbol;
enum class TypeModifiers : u8;
enum class KeywordID : u8;

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
	void ParseDeclaration(Ref<InterpreterContext> aContext) const;
	TypeModifiers ParseTypeModifiers(Ref<InterpreterContext> aContext) const;
	Ref<ObjectSymbol> ParseObject(Ref<InterpreterContext> aContext, TypeModifiers aModifiers) const;
};
