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
