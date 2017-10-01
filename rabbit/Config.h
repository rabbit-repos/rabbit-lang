#pragma once
#include "Types.h"
#include "ProjectType.h"
#include "json.h"

class String;

class Config
{
public:
	Config() { }
	~Config() { }

	void OpenProject(ConstRef<String> aPath);

	ProjectType GetProjectType() const;

private:
	ProjectType myProjectType;
	void ReadProject(ConstRef<json> aDocument);
};

extern Config gConfig;
