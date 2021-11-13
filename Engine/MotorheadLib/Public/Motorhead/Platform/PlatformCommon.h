#pragma once

#include "Window.h"

#ifdef PLATFORM_WIN64
#include "Motorhead/MSWindows/MSWinCommon.h"
#else
#error One plateform must be set
#endif
