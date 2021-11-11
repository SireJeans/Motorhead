#pragma once

#include "Core/CoreCommon.h"
#include "Engine/EngineCommon.h"
#include "Platform/PlatformCommon.h"
#ifdef _WIN64
#include "MSWindows/MSWinCommon.h"
#else
#error A Platform specific code have to be selected
#endif

