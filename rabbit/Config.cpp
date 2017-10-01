#include "pch.h"
#include "Config.h"
#include "StringData.h"
#include "String.h"
#include "ResizableArray.h"
#include <fstream>
#include <iostream>

Config gConfig;

void Config::OpenProject(ConstRef<String> aPath)
{
	Const<String> trimmedPath = aPath.Trim();

	std::wstring FilePath;

	if (trimmedPath.EndsWith(L".json"))
	{
		FilePath = trimmedPath.ToWideString();
	}
	else
	{
		// TODO: Find suitable project file within directory
		abort();
	}

	json document;
	std::ifstream file(FilePath);
	file >> document;

	ReadProject(document);
}

void Config::ReadProject(ConstRef<json> aDocument)
{
	std::cout << aDocument["projectType"].get<StringData>() << std::endl;
}

ProjectType Config::GetProjectType() const
{
	return myProjectType;
}
