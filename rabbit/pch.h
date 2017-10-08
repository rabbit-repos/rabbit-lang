#pragma once

#ifdef _MSC_VER
	#define LOOP_HINT(n) _Pragma("loop ( hint_parallel(n) )")
	// Ignore vector dependencies, should be used together with LOOP_HINT
	#define LOOP_HINT_IVDEP() _Pragma("loop ( ivdep )")
#else
	#define LOOP_HINT(n)
	#define LOOP_HINT_IVDEP()
#endif

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <xutility>
#include <type_traits>
#include <random>

#pragma warning ( push )
#pragma warning ( disable : 4706 )
#include "json.h"
#pragma warning ( pop )

constexpr size_t KiloByte = 1024;
constexpr size_t MegaByte = KiloByte * 1024;
constexpr size_t GigaByte = MegaByte * 1024;

#include "Types.h"

using json = nlohmann::json;

#include "ResizableArray.h"
#include "List.h"
#include "StringData.h"
#include "String.h"

inline void RandomizeData(Const<RawPtr> aData, Const<size> aSize)
{
	static std::random_device device;
	static Const<std::uniform_int_distribution<size>> d(MinOf<size>, MaxOf<size>);

	Const<size> num = aSize / sizeof size;
	for (size i = 0; i < num; ++i)
	{
		Const<size> value = d(device);
		memcpy(&reinterpret_cast<Ptr<u8>>(aData)[i * sizeof size], &value, sizeof value);
	}

	Const<size> value = d(device);
	size remaining = aSize - num * sizeof size;
	if (remaining > 0)
		memcpy(&reinterpret_cast<Ptr<u8>>(aData)[aSize - remaining], &value, remaining);
}
