#include "pch.h"
#include "Config.h"
#include "StringData.h"
#include "String.h"
#include "ResizableArray.h"

Const<StringData> gDefaultProjectName(L"output");
Const<StringData> gDefaultProjectType(L"executable");
constexpr i32 MaxPath = 512;

Config::Config()
	: myProjectName(), myProjectType(ProjectType::Unknown), myOutputExecutionTime(false), myOutputLexResults(false)
{
}

Config::Config(RValue<Config> aMove)
	: Config()
{
	*this = std::move(aMove);
}

Ref<Config> Config::operator=(RValue<Config> aMove)
{
	myProjectName = std::move(aMove.myProjectName);
	myProjectType = std::move(aMove.myProjectType);
	myOutputExecutionTime = std::move(aMove.myOutputExecutionTime);
	myOutputLexResults = std::move(aMove.myOutputLexResults);
	return *this;
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

	std::wifstream file(FilePath, std::ios::in);
	json document;
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
	myProjectName = ReadValue<StringData>(aDocument, L"projectName", gDefaultProjectName);

	// Project Type
	Const<StringData> projectType(ReadValue<StringData>(aDocument, L"projectType", gDefaultProjectType));
	
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
	// PERF: ToWideString allocates on the heap, not exactly ideal, would be better to pass in Ptr<Char> with length och null terminated stack allocated one
	auto it = aNode.find(aProperty.ToWideString());
	if (it == aNode.end())
		return T(aDefault);
	return it->get<T>();
}

bool HasValue(ConstRef<json> aNode, ConstRef<String> aProperty)
{
	// PERF: ToWideString allocates on the heap, not exactly ideal, would be better to pass in Ptr<Char> with length och null terminated stack allocated one
	auto it = aNode.find(aProperty.ToWideString());
	return it != aNode.end();
}
