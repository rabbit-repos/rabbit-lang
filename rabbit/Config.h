#pragma once
#include "ProjectType.h"

class Config
{
public:
	Config();
	Config(ConstRef<String> aPath);
	~Config() { }

	Ref<Config> operator=(RValue<Config> aMove);

	ConstRef<StringData> GetProjectName() const { return myProjectName; }
	ProjectType GetProjectType() const { return myProjectType; }
	bool GetOutputExecutionTime() const { return myOutputExecutionTime; }
	bool GetOutputLexResults() const { return myOutputLexResults; }

	ConstRef<List<StringData>> GetSourceFiles() const { return mySourceFiles; }

private:
	void ReadProject(ConstRef<json> aDocument);

	List<StringData> mySourceFiles;

	StringData myProjectName;
	ProjectType myProjectType;
	bool myOutputExecutionTime;
	bool myOutputLexResults;
};
