#pragma once

#pragma warning(disable:4530)


#if !defined(MHLOG_COMPILE_TIME_LEVEL)
#define MHLOG_COMPILE_TIME_LEVEL		MHLOG_LEVEL_TRACE
#endif

// API exposure
#ifdef BUILD_DLL
	#define CORE_API __declspec()
#else
	#define CORE_API
#endif


//#define USE_UTF16 1
