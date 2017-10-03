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
#include "json.h"

#include "Types.h"
