#pragma once

#include "Window.h"

#ifdef PLATFORM_WIN64
	#include "MSWindows/MSWinCommon.h"
#else
	#error One plateform must be set
#endif
