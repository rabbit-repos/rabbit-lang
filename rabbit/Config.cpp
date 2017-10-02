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

String Config::GetProjectName() const
{
	return myProjectName;
}

template <typename T>
T ReadValue(ConstRef<json> aNode, ConstRef<String> aProperty, ConstRef<T> aDefault);

void Config::ReadProject(ConstRef<json> aDocument)
{
	// Project Name
	myProjectName = ReadValue<StringData>(aDocument, L"projectName", L"output");

	// Project Type
	Const<StringData> projectType(ReadValue<StringData>(aDocument, L"projectType", L"executable"));
	
	if (String(L"executable").EqualsIgnoreCase(projectType))
	{
		myProjectType = ProjectType::Executable;
	}
	else if (String(L"library").EqualsIgnoreCase(projectType))
	{
		myProjectType = ProjectType::Library;
	}
	else
	{
		myProjectType = ProjectType::Unknown;
	}

	// Output Execution Time
	myOutputExecutionTime = ReadValue<bool>(aDocument, L"outputExecutionTime", false);

	// Output Lex Results
	myOutputLexResults = ReadValue<bool>(aDocument, L"outputLexResult", false);
}

ProjectType Config::GetProjectType() const
{
	return myProjectType;
}

bool Config::GetOutputExecutionTime() const
{
	return myOutputExecutionTime;
}

bool Config::GetOutputLexResults() const
{
	return myOutputLexResults;
}

template <typename T>
T ReadValue(ConstRef<json> aNode, ConstRef<String> aProperty, ConstRef<T> aDefault)
{
	// PERF: ToASCII will allocate on the heap, would be nice to search without taking a copy (jsfmcpp uses i8 chars)
	auto it = aNode.find(aProperty.ToASCII());
	if (it == aNode.end())
		return aDefault;
	return it->get<T>();
}
