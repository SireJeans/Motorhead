#pragma once

#include "PlatformMemory.h"
#include "Window.h"

#ifdef PLATFORM_WIN64
	#include "MSWindows/MSWinCommon.h"
#else
	#error One plateform must be set
#endif