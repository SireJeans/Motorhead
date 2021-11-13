#pragma once

#pragma warning(disable:4530)

#ifdef _WIN64
#define PLATFORM_WIN64
#else
#error Target platform have to be defined
#endif

#if !defined(MHLOG_COMPILE_TIME_LEVEL)
#define MHLOG_COMPILE_TIME_LEVEL		MHLOG_LEVEL_TRACE
#endif
