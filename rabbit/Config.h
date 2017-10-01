#pragma once
#include "ProjectType.h"

class String;

class Config
{
public:
	Config() { }
	~Config() { }

	void OpenProject(ConstRef<String> aPath);

	ProjectType GetProjectType() const;

private:
	void ReadProject(ConstRef<json> aDocument);

	ProjectType myProjectType;
};
