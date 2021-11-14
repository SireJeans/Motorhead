#pragma once

#include "Build.h"

#ifndef PLATFORM_WIN64
	#define PLATFORM_WIN64		0
#endif

#if PLATFORM_WIN64
	// Nothing to do
#else
	#error Must choose a target platform
#endif

#ifndef DLLEXPORT
	#define DLLEXPORT
	#define DLLIMPORT
#endif
