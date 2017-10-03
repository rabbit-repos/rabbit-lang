#include "pch.h"
#include "Config.h"
#include "StringData.h"
#include "String.h"
#include "ResizableArray.h"

Config::Config()
	: myProjectName(), myProjectType(ProjectType::Unknown), myOutputExecutionTime(false), myOutputLexResults(false)
{

}

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
bool HasValue(ConstRef<json> aNode, ConstRef<String> aProperty);

void Config::ReadProject(ConstRef<json> aDocument)
{
	*this = Config();

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

	// Source Files
	if (HasValue(aDocument, L"sourceFiles"))
	{
		json::array_t empty;
		json::array_t sourceFiles = ReadValue<json::array_t>(aDocument, L"sourceFiles", empty);

		for (ConstRef<json> node : sourceFiles)
		{
			mySourceFiles.Add(node.get<StringData>());
		}
	}
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

ConstRef<List<StringData>> Config::GetSourceFiles() const
{
	return mySourceFiles;
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

bool HasValue(ConstRef<json> aNode, ConstRef<String> aProperty)
{
	// PERF: ToASCII will allocate on the heap, would be nice to search without taking a copy (jsfmcpp uses i8 chars)
	auto it = aNode.find(aProperty.ToASCII());
	return it != aNode.end();
}
