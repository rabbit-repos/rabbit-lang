#pragma once

#ifdef _MSC_VER
	#define LOOP_HINT(n) _Pragma("loop ( hint_parallel(n) )")
	// Ignore vector dependencies, should be used together with LOOP_HINT
	#define LOOP_HINT_IVDEP() _Pragma("loop ( ivdep )")
	#define FatalError() { __debugbreak(); abort(); }
#else
	#define LOOP_HINT(n)
	#define LOOP_HINT_IVDEP()
	#define FatalError() abort();
#endif

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <xutility>
#include <type_traits>
#include <random>
#include <strstream>

#define CHECK_ENUM_BITFIELD_LENGTH ,\
	ZInternal_LastAdded,\
	ZInternal_Previous = ZInternal_LastAdded - 1\
	static_assert(std::numeric_limits<std::underlying_type_t<decltype(ZInternal_LastAdded)>> > Z_InternalPrevious, "Bitfield does not fit in enum");

// For now (hopefully)
#include <Windows.h>
#undef min
#undef max
#undef ERROR

#include "Types.h"

#pragma warning ( push )
#pragma warning ( disable : 4706 )
#include <json.h>
using json = nlohmann::json;
#pragma warning ( pop )

#define wcout __USE__PRINT
#define cout __USE__PRINT

#define ERROR(e) { PrintLine(e); FatalError(); }

constexpr size_t KiloByte = 1024;
constexpr size_t MegaByte = KiloByte * 1024;
constexpr size_t GigaByte = MegaByte * 1024;

class StringData;
template <typename TFirst, typename TSecond = void, typename ...TOthers>
void Append(StringData & aStringData, const TFirst & aValue);
template <typename TFirst, typename TSecond, typename ...TOthers>
void Append(StringData & aStringData, const TFirst & aValue, const TSecond & aSecondValue, TOthers &&... aOthers);
template <typename ...TOthers>
StringData AppendString(TOthers &&... aOthers);
template <typename ...TOthers>
void Print(TOthers &&... aOthers);
template <typename ...TOthers>
void PrintLine(TOthers &&... aOthers);

#include "ResizableArray.h"
#include "List.h"
#include "StringData.h"
#include "String.h"

#undef wcout
#undef cout

template <typename TFirst, typename TSecond, typename ...TOthers>
void Append(StringData & aStringData, const TFirst & aValue)
{
	static_assert(!std::is_same_v<char, std::remove_all_extents_t<TFirst>>, "Regular characters may not be printed, use wide strings instead.");
	aStringData.Append(aValue);
}

template <typename TFirst, typename TSecond, typename ...TOthers>
void Append(StringData & aStringData, const TFirst & aValue, const TSecond & aSecondValue, TOthers &&... aOthers)
{
	Append(aStringData, aValue);
	Append(aStringData, aSecondValue, aOthers...);
}

template <typename ...TOthers>
StringData AppendString(TOthers &&... aOthers)
{
	StringData string;
	Append(string, aOthers...);
	return string;
}

template <typename ...TOthers>
void Print(TOthers &&... aOthers)
{
	StringData string;
	Append(string, aOthers...);

	OutputDebugStringW(string.ToCString());
	std::wcout << string;
}

template <typename ...TOthers>
void PrintLine(TOthers &&... aOthers)
{
	Print(aOthers...);
	OutputDebugStringW(L"\r\n");
	std::wcout << std::endl;
}

#define wcout __USE__PRINT
#define cout __USE__PRINT

void RandomizeData(Const<RawPtr> aData, Const<size> aSize);
