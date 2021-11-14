#pragma once

#ifdef _WIN64
	#define PLATFORM_WIN64		1
#endif


#ifndef BUILD_DLL
	#define BUILD_DLL			0
#endif

#ifndef USE_UTF16OR32
	#define USE_UTF16OR32		0
#endif
