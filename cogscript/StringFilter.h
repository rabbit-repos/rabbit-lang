#pragma once

template <typename T>
class OperatorMap
{
public:
	Ref<T> GetValue(ConstRef<String> aKey) const;

private:
	Ptr<T> myValue;
	std::unordered_map<Char, StringMap> myMap;
};
