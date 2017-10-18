#include "pch.h"
#include "Config.h"
#include "StringData.h"
#include "String.h"
#include "ResizableArray.h"

json ReadFile(ConstRef<String> aPath);
static Const<json> gDefaultConfig = ReadFile(L"default-project.json");

Config::Config()
{
	ReadProject(gDefaultConfig);
}

Config::Config(ConstRef<String> aPath)
{
	ReadProject(ReadFile(aPath));
}

#define RBT_MOVE(p) p = std::move(aMove.p)

Ref<Config> Config::operator=(RValue<Config> aMove)
{
	RBT_MOVE(mySourceFiles);
	RBT_MOVE(myProjectName);
	RBT_MOVE(myProjectType);
	RBT_MOVE(myOutputExecutionTime);
	RBT_MOVE(myOutputLexResults);
	return *this;
}

#undef RBT_MOVE

template <typename T>
bool ReadValue(ConstRef<json> aNode, ConstRef<String> aProperty, Out<T> aValueToSet);

json ReadFile(ConstRef<String> aPath)
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
		PrintLine("Not implemented");
		abort();
	}

	std::wifstream file(FilePath, std::ios::in);
	json document;
	file >> document;
	return document;
}

void Config::ReadProject(ConstRef<json> aDocument)
{
	ReadValue<StringData>(aDocument, L"projectName", myProjectName);
	
	// Project Type
	StringData projectType;
	if (ReadValue<StringData>(aDocument, L"projectType", projectType))
	{
		if (String(L"executable").EqualsIgnoreCase(projectType))
			myProjectType = ProjectType::Executable;
		else if (String(L"library").EqualsIgnoreCase(projectType))
			myProjectType = ProjectType::Library;
		else
			myProjectType = ProjectType::Unknown;
	}
	else
		myProjectType = ProjectType::Executable;

	ReadValue<bool>(aDocument, L"outputExecutionTime", myOutputExecutionTime);
	ReadValue<bool>(aDocument, L"outputLexResult", myOutputLexResults);

	json::array_t sourceFiles;
	if (ReadValue<json::array_t>(aDocument, L"sourceFiles", sourceFiles))
		for (ConstRef<json> node : sourceFiles)
			mySourceFiles.Add(node.get<StringData>());
}

template <typename T>
bool ReadValue(ConstRef<json> aNode, ConstRef<String> aProperty, Out<T> aValueToSet)
{
	// PERF: ToWideString allocates on the heap, not exactly ideal, would be better to pass in Ptr<Char> with length and null terminated stack allocated one
	auto it = aNode.find(aProperty.ToWideString());
	if (it == aNode.end())
	{
		if (&aNode == &gDefaultConfig)
			abort();

		return ReadValue(gDefaultConfig, aProperty, aValueToSet);
	}

	aValueToSet = it->get<T>();
	return true;
}
