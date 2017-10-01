#include "pch.h"
#include "Config.h"
#include "StringData.h"
#include "String.h"
#include "ResizableArray.h"

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
		std::cout << "Not implemented" << std::endl;
		abort();
	}

	json document;
	std::ifstream file(FilePath);
	file >> document;

	ReadProject(document);
}

void Config::ReadProject(ConstRef<json> aDocument)
{
	StringData projectType = aDocument.value<StringData>("hej", L"apor");
	
}

ProjectType Config::GetProjectType() const
{
	return myProjectType;
}
