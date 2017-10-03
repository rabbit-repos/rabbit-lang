#pragma once
#include "ProjectType.h"
#include "StringData.h"

class String;

class Config
{
public:
	Config();
	~Config() { }

	void OpenProject(ConstRef<String> aPath);

	String GetProjectName() const;
	ProjectType GetProjectType() const;
	bool GetOutputExecutionTime() const;
	bool GetOutputLexResults() const;

	ConstRef<List<StringData>> GetSourceFiles() const;

private:
	void ReadProject(ConstRef<json> aDocument);

	List<StringData> mySourceFiles;

	StringData myProjectName;
	ProjectType myProjectType;
	bool myOutputExecutionTime;
	bool myOutputLexResults;
};
